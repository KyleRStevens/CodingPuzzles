#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstdint>
#include <map>
#include <mutex>
#include <thread>
#include <array>

#define TESTING 1

#ifdef _POSIX_THREADS
#define PTHREAD_SUPPORTED
#include <pthread.h>
#endif
constexpr int MAX_THREADS = 16;
class Solution_RabbitHole2v2
{
public:

public:
	struct Link;
	struct Page
	{
		#if (TESTING)
		Page(int ID) : pageID(ID) { /* Do nothing */ }
		int pageID = 0; // Doesn't *actually* need to be stored - this just makes it convenient to debug
		#endif

		size_t maxVisitors = 0;
		std::map<int /*to page ID*/, int /*link ID*/> links;
	};

	struct Link
	{
		#if (TESTING)
		Link(int ID) : linkID(ID) { isVisited.fill(0); }
		int linkID = 0; // Doesn't *actually* need to be stored - this just makes it convenient to debug
		#endif

		Page* toPage = nullptr;
		std::array<uint8_t, MAX_THREADS> isVisited; // 0 = no, 1 = yes once, 2 = yes twice (I'm hoping you don't need to visit more than twice because then, how do you not get in a loop?)
	};

private:
	size_t m_maxPages = 0;
	std::mutex m_updateMaxMutex;
	std::mutex m_getPageMutex;

	inline void updateMaxPages(size_t newValue)
	{
		std::lock_guard<std::mutex> lock(m_updateMaxMutex);

		if (newValue > m_maxPages)
		{
			m_maxPages = newValue;
		}
	}

	int m_currentPageToCheck = 0;
	inline int GetNextPageToCheck()
	{
		std::lock_guard<std::mutex> lock(m_getPageMutex);

		m_currentPageToCheck++;
		return m_currentPageToCheck;
	}

public:
	void DFS(std::vector<Page>& pages, std::vector<Link>& links, Page* pThisPage, std::map<Page*, int>& visitedPages, const uint8_t threadID)
	{
		// Add to the counter of how many times this page was visited in the current path
		visitedPages[pThisPage]++;
	
		// Save the global maxVisiters (TODO: move into below if statement?)
		updateMaxPages(visitedPages.size());
		
		// IF the this page's maxVisitors (will have) changed (OR IF EQUAL because...? I don't 100% understand yet, but it fixes one bug that was found)
		if (visitedPages.size() >= pThisPage->maxVisitors)
		{
			// Save the change
			pThisPage->maxVisitors = visitedPages.size();
	
			// For each link in the current page
			for (const auto& [toPageID, linkID] : pThisPage->links)
			{
				Link* pLink = &links[linkID];
				
				// IF the link is unvisited OR visited only once
				if (links[linkID].isVisited[threadID] < 2)
				{
					// Mark the link as visited again (incriment the counter)
					links[linkID].isVisited[threadID]++;
	
					// Recurse into the page for that link
					DFS(pages, links, pLink->toPage, visitedPages, threadID);
	
					// Mark one less visit
					links[linkID].isVisited[threadID]--;
				}
			}
		}
	
		// Remove one visit count for this page (if it goes to 0, remove it from the map entirely)
		if (--visitedPages[pThisPage] == 0)
		{
			visitedPages.erase(pThisPage);
		}
	}

	void DoSearch(std::vector<Page>& pages, std::vector<Link>& links, const uint8_t threadID)
	{
		// Get the next page that hasn't yet been searched from
		int pageToStartOn = GetNextPageToCheck();

		// Set up a mapping to store all the pages visited in the current path and their corresponding number of times visited for the current path (that way we know when to remove it from the list)
		std::map<Page*, int /*count*/> visitedPages;

		// Make sure we're on a valid page (if not, we're done)
		while (pageToStartOn < pages.size())
		{
			// Start with no pages visited
			visitedPages.clear();

			// Using a depth-first approach (so we only need to store 1 path context at a given time), scan through each path
			DFS(pages, links, &pages[pageToStartOn], visitedPages, threadID);

			// Get the next page to start on
			pageToStartOn = GetNextPageToCheck();
		}
	}

	void Search(std::vector<Page>& pages, std::vector<Link>& links)
	{
		#if (PTHREAD_SUPPORTED)
		std::vector<std::thread> threads;

		// Get number of available logical cores
		unsigned int numLogicalCores = std::thread::hardware_concurrency();
		if (numLogicalCores == 0)
		{
			// Default to 1 if 0 was returned
			numLogicalCores = 1;
		}

		// Reserve space for threads
		threads.reserve(numLogicalCores);

		// For each available logical core, spawn a new thread on DoSearch
		for (uint8_t i = 0; i < numLogicalCores && i < MAX_THREADS; ++i)
		{
			const uint8_t threadID = i;
			threads.emplace_back(&Solution_RabbitHole2v2::DoSearch, this, std::ref(pages), std::ref(links), threadID);
		}

		// Join threads
		for (auto& thread : threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
		#else
		DoSearch(pages, links, 0);
		#endif
	}

	// Currently passing 12/22 test cases... (7 wrong answer, time limited on 3)
	int getMaxVisitableWebpages(int N, int M, std::vector<int>& A, std::vector<int>& B)
	{
		// Build the entire graph of pages (vertices)
		#if (TESTING)
			std::vector<Page> pages;
			pages.reserve(N + 1);
			for (int i = 0; i < N + 1; ++i)
			{
				// Use the index 'i' as the "page ID" for O(1) access to a page given the ID
				pages.emplace_back(i);
			}
		#else
			std::vector<Page> pages(N + 1);
		#endif

		// Build the entire graph of links (edges)
		#if (TESTING)
			std::vector<Link> links;
			links.reserve(M);
		#else
			std::vector<Link> links(M);
		#endif
		for (int i = 0; i < M; ++i)
		{
			int fromPage = A[i];
			int toPage = B[i];

			// Use 'i' as the unique ID for each link
			int linkID = i;

			// Assign each link a unique ID - using index 'i' for O(1) access to a link given the ID
			#if (TESTING)
				links.emplace_back(linkID);
			#endif

			// Check if this is a duplicate link (no need to store duplicates)
			if (pages[fromPage].links.find(toPage) == pages[fromPage].links.end())
			{
				// If not a duplicate, add the link to the 'from' page
				pages[fromPage].links[toPage] = linkID;

				// Make the actual link in the Link object
				links[linkID].toPage = &pages[toPage];
			}
		}

		// Do the search
		Search(pages, links);

		// Return the found maximum
		return m_maxPages;
	}
};