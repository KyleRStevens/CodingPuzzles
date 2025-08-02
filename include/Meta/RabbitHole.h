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

// Meta Puzzle: Rabbit Hole
class Solution_RabbitHole
{
private:
	int m_maxVisitableWebpages = 1;

private:
	struct Page
	{
		bool visited = false;
		bool queued = false;
		int bestPathEndpoint = -1;
		int bestPathNext = -1;
		int maxVisitablePagesSize = 1;
		std::set<int> fromLinks; // O(N) space
		std::set<int> maxVisitablePages; // O(N) space - TODO: Instead of every page storing this, only save the next item on the best path unless the path contains a "self" (cycle), in which case that page can store the full path set from there
	};

private:
	void SaveBestPath(std::vector<Page>& pages, const int startPage, std::set<int>& pathSet)
	{
		int page = startPage;

		// Insert the self reference and move to the next
		pathSet.insert(page);
		page = pages[page].bestPathNext;

		while (page != -1 && page != startPage)
		{
			// If we reached a page that has the saved path set, we can simply insert that whole set and return
			if (pages[page].maxVisitablePages.size() != 0)
			{
				pathSet.insert(pages[page].maxVisitablePages.begin(), pages[page].maxVisitablePages.end());
				return;
			}

			// Otherwise, insert the current page and move on to the next
			pathSet.insert(page);
			page = pages[page].bestPathNext;
		}
	}
	
	bool CheckBestPathForPage(std::vector<Page>& pages, const int startPage, const int targetPage)
	{
		int page = startPage;

		while (page != -1)
		{
			// If we reached a page that has the saved path set, we can simply check if the set contains the target page
			if (pages[page].maxVisitablePages.size() != 0)
			{
				if (pages[page].maxVisitablePages.find(targetPage) == pages[page].maxVisitablePages.end())
				{
					// The target page was NOT found to be in the path
					return false;
				}
				else
				{
					// The target page WAS found to be in the path
					return true;
				}
			}

			// If the next page we'd be going to is the target page, we can just return true
			if (pages[page].bestPathNext == targetPage)
			{
				// The target page WAS found to be in the path
				return true;
			}

			// Otherwise, either move to the next page in the path (ends the search if we've reached the end of the path)
			page = pages[page].bestPathNext;
		}

		// The target page was NOT found to be in the path
		return false;
	}

	void DoUpdate(std::vector<Page>& pages, int page, int updaterPage)
	{
		// Set equal to the updater's set
		//pages[page].maxVisitablePages = pages[updaterPage].maxVisitablePages;

		// Add back in the self-reference
		//pages[page].maxVisitablePages.insert(page);

		// Mark the path of this best visit path - next
		pages[page].bestPathNext = updaterPage;

		// Mark the path of this best visit path - endpoint
		if (pages[updaterPage].bestPathEndpoint != -1)
		{
			pages[page].bestPathEndpoint = pages[updaterPage].bestPathEndpoint;
		}
		else
		{
			pages[page].bestPathEndpoint = updaterPage;
		}

		// Update the maxVisitablePagesSize as long as the current path doesn't include this page itself
		if (CheckBestPathForPage(pages, updaterPage, page))
		{
			// If the path DOES contain this page already, we'll save the whole path set to this page
			//pages[page].maxVisitablePages.clear(); // ????
			SaveBestPath(pages, page, pages[page].maxVisitablePages);

			// ??
			pages[page].maxVisitablePagesSize = static_cast<int>(pages[page].maxVisitablePages.size());
		}
		else
		{
			// If the path does NOT contain this page already, we'll update our path size
			pages[page].maxVisitablePagesSize = pages[updaterPage].maxVisitablePagesSize + 1;
		}
	}

	bool UpdateMaxVisitablePages(std::vector<Page>& pages, int page, int updaterPage)
	{
		// Check if we actually need to do an update...
		bool maxVisitablePagesUpdated = false;
		if (pages[updaterPage].maxVisitablePagesSize > pages[page].maxVisitablePagesSize)
		{
			// Do the update
			DoUpdate(pages, page, updaterPage);

			// Flag the update
			maxVisitablePagesUpdated = true;
		}
		else if (pages[updaterPage].maxVisitablePagesSize == pages[page].maxVisitablePagesSize)
		{
			// If it's the same size, but does NOT constain THIS page, then it will be bigger, so lets do the update
			if (CheckBestPathForPage(pages, updaterPage, page) == false)
			{
				// Do the update
				DoUpdate(pages, page, updaterPage);

				// Flag the update
				maxVisitablePagesUpdated = true;
			}
		}

		// Update the global max visitable pages size if necessary
		if (maxVisitablePagesUpdated)
		{
			m_maxVisitableWebpages = std::max(m_maxVisitableWebpages, pages[page].maxVisitablePagesSize);
		}

		// Return if there was an update or not
		return maxVisitablePagesUpdated;
	}

public:
	int getMaxVisitableWebpages(int N, std::vector<int>& L) // ~O(N* L)
	{
		// Create a container for the page data
		std::vector<Page> pages;
		pages.resize(N + 1); // O(N)

		// Build out the whole graph
		for (int i = 0; i < L.size(); ++i) // O(L) => O(L*logN)
		{
			int fromPage = i + 1;
			int toPage = L[i];

			// Add the "from" link in the "to" page
			pages[toPage].fromLinks.insert(fromPage); // O(logN)
		}

		// A queue for the "recursive" updating
		std::queue<int> pagesToUpdate;

		// For each page...
		for (int i = 1; i < pages.size(); ++i) // O(N) ==> Somewhere between O(N) & O(N^3)?
		{
			// Rather than starting at this page, start at the best (known) path's endpoint as starting from the end will result in less revisits during the recursive updating
			int startPage = i;
			if (pages[i].bestPathEndpoint != -1)
			{
				startPage = pages[i].bestPathEndpoint;
			}

			// If the page is NOT flagged as visited...
			if (pages[startPage].visited == false)
			{
				// Add the current start page to the queue
				pagesToUpdate.push(startPage);
				pages[startPage].queued = true;
				
				// Recursively update each "from" page's maxVisitablePages based on the current page
				while (pagesToUpdate.empty() == false) // O(N) ==> O(N^2) worst case, O(N+) average?
				{
					// Get the current page and remove from the queue
					int currentPage = pagesToUpdate.front();
					pagesToUpdate.pop();
					pages[currentPage].queued = false;

					// If the page isn't already visited...
					if (pages[currentPage].visited == false)
					{
						// Visit the page
						pages[currentPage].visited = true;

						// For each of its "from" links...
						for (const int& page : pages[currentPage].fromLinks) // O(N) in the worst case, but for average case, this (sort of / hopefully) doesn't count as additional time complexity because visited pages will be skipped (mostly), so the total number of true iterations is still ~N (where there's hopefully not many revisits)
						{
							// See if any of them get updated with this page's maxVisitablePages
							if (UpdateMaxVisitablePages(pages, page, currentPage))
							{
								// Only if the page has already been visited do we queue it to be visited again - if it hasn't been visited, it already will be! No need to keep queuing it redundent times as who knows how many other nodes will also try to do the same...
								if (pages[page].queued == false)
								{
									// If so, it might need to update on of its "from" pages, so add it to the queue
									pagesToUpdate.push(page);
									pages[page].queued = true;

									// Mark it as not visited even if it has been so we can re-update its connections if necessary
									pages[page].visited = false;
								}
							}
						}
					}
				}
			}
		}

		// Return
		return m_maxVisitableWebpages;
	}

	void Test()
	{
		std::vector<int> rabbitHoleLinks{ 2, 4, 2, 2, 3 };
		auto rabbitHoleResult = getMaxVisitableWebpages(5, rabbitHoleLinks);
	}
};