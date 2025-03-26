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

// Is this not an NP-Hard problem??
class Solution_RabbitHole
{
private:
	int m_maxVisitableWebpages = 1;

private:
	struct Page
	{
		std::set<int> fromLinks; // O(N) space
		std::set<int> maxVisitablePages; // O(N) space
	};

public:
	bool UpdateMaxVisitablePages(std::vector<Page>& pages, int page, int updaterPage)
	{
		// Check if we actually need to do an update...
		bool maxVisitablePagesUpdated = false;
		if (pages[updaterPage].maxVisitablePages.size() > pages[page].maxVisitablePages.size())
		{
			// Set equal to the updater's set
			pages[page].maxVisitablePages = pages[updaterPage].maxVisitablePages;

			// Add back in the self-reference
			pages[page].maxVisitablePages.insert(page);

			// Flag the update
			maxVisitablePagesUpdated = true;
		}
		else if (pages[updaterPage].maxVisitablePages.size() == pages[page].maxVisitablePages.size())
		{
			// If it's the same size, but does NOT constain THIS page, then it will be bigger, so lets do the update
			if (pages[updaterPage].maxVisitablePages.find(page) == pages[updaterPage].maxVisitablePages.end())
			{
				// Set equal to the updater's set
				pages[page].maxVisitablePages = pages[updaterPage].maxVisitablePages;

				// Add back in the self-reference
				pages[page].maxVisitablePages.insert(page);

				// Flag the update
				maxVisitablePagesUpdated = true;
			}
		}

		// Update the global max visitable pages size if necessary
		if (maxVisitablePagesUpdated)
		{
			m_maxVisitableWebpages = std::max(m_maxVisitableWebpages, static_cast<int>(pages[page].maxVisitablePages.size()));
		}

		// Return if there was an update or not
		return maxVisitablePagesUpdated;
	}

	int getMaxVisitableWebpages(int N, std::vector<int>& L) // ~O(N* L)
	{
		// Create a container for the page data
		std::vector<Page> pages;
		pages.resize(N + 1); // O(N)

		// An array of "visited" flags (for each page)
		std::vector<bool> visited;
		visited.resize(N + 1, false); // O(N)

		// A queue for the "recursive" (breadth-first) updating
		std::queue<int> pagesToUpdate;

		// For each link in L
		for (int i = 0; i < L.size(); ++i) // O(L) => ~O(N*L)
		{
			int fromPage = i + 1;
			int toPage = L[i];

			// Add the "from" link in the "to" page
			pages[toPage].fromLinks.insert(fromPage); // At least O(logN)

			// Add the "to" link in the "from" page (unused)
			//pages[fromPage].toLinks.insert(toPage); // At least O(logN)

			// Update the from page's maxVisitablePages based on the toPage
			bool maxVisitablePagesUpdated = UpdateMaxVisitablePages(pages, fromPage, toPage);

			// If the fromPage's maxVisitablePages updated...
			if (maxVisitablePagesUpdated)
			{
				// Also update each (next) "from" page's maxVisitablePages (recursively)
				pagesToUpdate.push(fromPage);
				while (pagesToUpdate.empty() == false) // ~O(N)
				{
					// Get the current page and remove from the queue
					int currentPage = pagesToUpdate.front();
					pagesToUpdate.pop();

					// If the page isn't already visited...
					if (visited[currentPage] == false)
					{
						// Visit the page
						visited[currentPage] = true;

						// For each of its "from" links...
						for (const int& page : pages[currentPage].fromLinks)
						{
							// See if any of them get updated with this page's maxVisitablePages
							if (UpdateMaxVisitablePages(pages, page, currentPage))
							{
								// If so, it might need to update on of its "from" pages, so add it to the queue
								pagesToUpdate.push(page);
								
								// Mark it as not visited even if it has been so we can actually update it
								visited[page] = false;
							}
						}
					}
				}

				// Reset the visited flags
				visited.clear();
				visited.resize(N + 1, false);
			}
		}

		// Return
		return m_maxVisitableWebpages;
	}
};