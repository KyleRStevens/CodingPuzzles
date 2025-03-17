#pragma once

// Standard
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>

class Solution_RabbitHole
{
private:
	int m_maxDepth = 1;

private:
	const int MAX_VISITS = 1;

private:
	struct Link
	{
		int toPageIndex = -1;
		int visitCount = 0;
	};

	struct Page
	{
		int visitCount = 0;
		int maxDepth = 0;
		std::vector<Link> links;
	};

public:
	void PageDFSWithBacktracking(Page* pCurrentPage, std::vector<Page>& pages, int& currentDepth) // O(L)
	{
		// Only visit a page if it is possible to get a larger result than what we've already found for it
		if (pCurrentPage->maxDepth <= currentDepth)
		{
			// Visit current page
			pCurrentPage->visitCount++;

			// If this is the first visit of this branch
			if (pCurrentPage->visitCount == 1)
			{
				// Add to current depth counter
				currentDepth++;

				// Update global max depth if necessary
				if (currentDepth > m_maxDepth)
				{
					m_maxDepth = currentDepth;
				}

				// Update the current page's max depth if necessary
				if (currentDepth > pCurrentPage->maxDepth)
				{
					pCurrentPage->maxDepth = currentDepth;
				}
			}

			// For each link from this page
			for (Link& link : pCurrentPage->links) // O(L)
			{
				// Check if the link is valid to visit
				if (link.visitCount < MAX_VISITS)
				{
					// If so, visit the link
					link.visitCount++;

					// Recurse to the linked page
					PageDFSWithBacktracking(&pages[link.toPageIndex], pages, currentDepth);

					// Unvisit the link
					link.visitCount--;
				}
			}

			// Unvisit the current page
			pCurrentPage->visitCount--;

			// If this page is now unvisited
			if (pCurrentPage->visitCount == 0)
			{
				// Adust the current depth
				currentDepth--;
			}
		}
	}

	int getMaxVisitableWebpages(int N, std::vector<int> L) // O(N*L)
	{
		// Build graph of pages & links
		std::vector<Page> pages;
		pages.resize(N + 1);
		for (int i = 0; i < L.size(); ++i) // O(L)
		{
			// Make the link
			Page& fromPage = pages[i + 1];
			fromPage.links.push_back({ L[i], 0 });
		}

		// For each page as a start page...
		for (Page& page : pages) // O(N)
		{
			// Use a DFS to find the longest path of unvisited pages
			int currentDepth = 0;
			PageDFSWithBacktracking(&page, pages, currentDepth); // O(L)
		}

		return m_maxDepth;
	}
};