// This is (going to be) the multithreaded version of RabbitHole2v2
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

class Solution_RabbitHole2v2MT
{
public:
	struct Link;
	struct Page
	{
		Page(int ID) : pageID(ID) { /* Do nothing */ }

		int pageID = 0; // Doesn't *actually* need to be stored - this just makes it convenient to debug (TODO: Remove)
		size_t maxVisitors = 0;
		std::map<int /*to page ID*/, int /*link ID*/> links;
	};

	struct Link
	{
		Link(int ID) : linkID(ID) { /* Do nothing */ }

		int linkID = 0; // Doesn't *actually* need to be stored - this just makes it convenient to debug (TODO: Remove)
		Page* toPage = nullptr;
	};

private:
	size_t m_maxPages = 0;

	inline void updateMaxPages(size_t newValue)
	{
		if (newValue > m_maxPages)
		{
			m_maxPages = newValue;
		}
	}

public:
	void DFS(std::vector<Page>& pages, std::vector<Link>& links, Page* pThisPage, std::map<Page*, int>& visitedPages, std::set<Link*>& visitedLinks)
	{
		// Add to the counter of how many times this page was visited in the current path
		visitedPages[pThisPage]++;
	
		// Save the global maxVisiters (TODO: move into below if statement?)
		updateMaxPages(visitedPages.size());
		
		// IF the this page's maxVisitors (will have) changed
		if (visitedPages.size() > pThisPage->maxVisitors)
		{
			// Save the change
			pThisPage->maxVisitors = visitedPages.size();
	
			// For each link in the current page
			for (const auto& [toPageID, linkID] : pThisPage->links)
			{
				Link* pLink = &links[linkID];
				
				// IF the link is UNVISITED
				if (visitedLinks.find(pLink) == visitedLinks.end())
				{
					// Mark the link as visited
					visitedLinks.insert(pLink);
	
					// Recurse into the page for that link
					DFS(pages, links, pLink->toPage, visitedPages, visitedLinks);
	
					// Mark the link as unvisited
					visitedLinks.erase(pLink);
				}
			}
		}
	
		// Remove one visit count for this page (if it goes to 0, remove it from the map entirely)
		if (--visitedPages[pThisPage] == 0)
		{
			visitedPages.erase(pThisPage);
		}
	}

	// Currently passing 12/22 test cases... (7 wrong answer, time limited on 3)
	int getMaxVisitableWebpages(int N, int M, std::vector<int>& A, std::vector<int>& B)
	{
		// Build the entire graph of pages (vertices)
		std::vector<Page> pages;
		pages.reserve(N + 1);
		for (int i = 0; i < N + 1; ++i)
		{
			// Use the index 'i' as the "page ID" for O(1) access to a page given the ID
			pages.emplace_back(i);
		}

		// Build the entire graph of links (edges)
		std::vector<Link> links;
		links.reserve(M);
		for (int i = 0; i < M; ++i)
		{
			int fromPage = A[i];
			int toPage = B[i];

			// Use 'i' as the unique ID for each link
			int linkID = i;

			// Assign each link a unique ID - using index 'i' for O(1) access to a link given the ID
			links.emplace_back(linkID);

			// Check if this is a duplicate link (no need to store duplicates)
			if (pages[fromPage].links.find(toPage) == pages[fromPage].links.end())
			{
				// If not a duplicate, add the link to the 'from' page
				pages[fromPage].links[toPage] = linkID;

				// Make the actual link in the Link object
				links[linkID].toPage = &pages[toPage];
			}
		}

		// Set up a mapping to store all the pages visited in the current path and their corresponding number of times visited for the current path (that way we know when to remove it from the list)
		std::map<Page*, int /*count*/> visitedPages;

		// This simply stores all the links in the current path so we know what's been visited (TODO: This could be a flag set directly in the Link class if we also store a link ID in order to retrieve a particular link in O(1) - so long as we're not using multithreading)
		std::set<Link*> visitedLinks;

		// Using a depth-first approach (so we only need to store 1 path context at a given time), scan through each path
		for (int i = 1; i < pages.size(); ++i)
		{
			DFS(pages, links, &pages[i], visitedPages, visitedLinks);
		}

		// Return the found maximum
		return m_maxPages;
	}
};