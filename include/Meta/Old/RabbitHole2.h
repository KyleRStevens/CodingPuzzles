#pragma once

// Standard
#include <vector>
#include <iostream>
#include <unordered_set>

class Solution_RabbitHole2
{
public:
	struct Page
	{
		int maxVisitors = 0;
		int pageID = 0;

		std::unordered_set<Page*> links;

		std::vector<bool> visitersList;
	};

	struct Link
	{
		int fromPageID = 0;
		int toPageID = 0;

		// Simply used for sorting the links for better include ordering
		int occurenceDiff = 0;
	};

	struct PageLinkOccurances
	{
		int fromOccurences = 0;
		int toOccurences = 0;
	};

private:
	void updateMaxVisitors(Page* pFromPage, Page* pThisPage, std::vector<bool>& visitedList)
	{
		// Make sure this node has not already been visited during this update cycle (if it has, just return)
		if (visitedList[pThisPage->pageID] == false)
		{
			// Mark the current node as visited
			visitedList[pThisPage->pageID] = true;

			// If the potential new max already factors in this page, account for this so we don't double-count this page
			int potentialNewMaxVisitors = pFromPage->maxVisitors + 1;
			if (pFromPage->visitersList.empty() == false && pFromPage->visitersList[pThisPage->pageID] == true)
			{
				potentialNewMaxVisitors--;
			}

			// Update this node's max visitors
			int oldMaxVisitors = pThisPage->maxVisitors;
			pThisPage->maxVisitors = std::max(oldMaxVisitors, potentialNewMaxVisitors);

			// Recurse for each linked node ONLY IF the maxVisiters actually changed!
			if (oldMaxVisitors != pThisPage->maxVisitors)
			{
				// If the value did change, save the new visited list for this page
				if (pFromPage->visitersList.empty())
				{
					// If the 'from' page's visiter list hasn't been built yet, we'll use the current recursion's visitation list
					pThisPage->visitersList = visitedList;
				}
				else
				{
					// If the 'from' page's visiter list HAS been built, we'll use it since that's the path that the new visiters value comes from
					pThisPage->visitersList = pFromPage->visitersList;

					// Remembering to incude this page's flag iteself in the list
					pThisPage->visitersList[pThisPage->pageID] = true;
				}

				// Update each linked page
				for (Page* pLinkedPage : pThisPage->links)
				{
					updateMaxVisitors(pThisPage, pLinkedPage, visitedList);
				}
			}

			// Before we exit this recursion level, remove the current page from the visited flags
			visitedList[pThisPage->pageID] = false;
		}
	}

public:
	int getMaxVisitableWebpagesInternal(int N, std::vector<Link>& links)
	{
		int maxVisitableWebpages = 0;

		// Create a page (node) for each page that exists, where the index of the page node is the page ID of that page (resulting in O(1) lookups)
		std::vector<Page> pages(N + 1);
		for (int i = 0; i < pages.size(); ++i)
		{
			pages[i].pageID = i;
		}

		// For each link, create the link, then update the max visitors of each node (recursive)
		for (int i = 0; i < links.size(); ++i)
		{
			int fromPageID = links[i].fromPageID;
			int toPageID = links[i].toPageID;

			// Create link
			pages[fromPageID].links.insert(&pages[toPageID]);

			// Create a list of already-visited pages (effectively a bitset) so we can avoid double-counting and infinite looping during the recursive calls
			std::vector<bool> visitedList;
			visitedList.resize(pages.size(), false);

			// Make sure the 'from' page is already visited
			visitedList[fromPageID] = true;
			
			// Update the max visiters of each relevant node
			updateMaxVisitors(&pages[fromPageID], &pages[toPageID], visitedList);
		}

		// Find the page with the largest maxVisitors value
		for (Page& page : pages)
		{
			if (page.maxVisitors > maxVisitableWebpages)
			{
				maxVisitableWebpages = page.maxVisitors;
			}
		}

		// Return the found maximum (+1 to account for the page that has this number of max visiters)
		return maxVisitableWebpages + 1;
	}

	// Currently passing 10/22 test cases...
	int getMaxVisitableWebpages(int N, int M, std::vector<int> A, std::vector<int> B)
	{
		int maxVisitableWebpages = 0;

		// Heuristic: Building links 3->9 then 9->8 is better than building links 9->8 then 3->9 as there will be less recursion
		// So, can we sort A & B such that we minimize the less preferable ordering and maximize the more preferable ordering?
		std::vector<PageLinkOccurances> pageLinkOccurences(N + 1);

		// Create a list of links that we can sort
		std::vector<Link> links(A.size());

		// Fill out the list of links, also counting up the occurances of each page in A & B
		for (int i = 0; i < A.size(); ++i)
		{
			int fromPage = A[i];
			int toPage = B[i];

			// Fill out the link info
			links[i].fromPageID = fromPage;
			links[i].toPageID = toPage;

			// Update the occurances
			pageLinkOccurences[fromPage].fromOccurences++;
			pageLinkOccurences[toPage].toOccurences++;
		}

		// Just set this to false if this was actually a dumb idea (using the small examples it did reduce the number of recursion calls by ~10%...)
		const bool USING_SORTED_LINKS_HEURISTIC = true;
		if (USING_SORTED_LINKS_HEURISTIC)
		{
			// Save the occurence differences into the links themselves so we can sort by that
			for (Link& link : links)
			{
				link.occurenceDiff = pageLinkOccurences[link.fromPageID].fromOccurences - pageLinkOccurences[link.fromPageID].toOccurences;
			}

			// Sort the list of links by the occurence difference for either the 'to' or 'from' page - it doesn't really matter which (as long ad you match the sorting direction accordingly)
			auto sortByOccuranceDiff = [](Link& a, Link& b) { return a.occurenceDiff > b.occurenceDiff; };
			std::sort(links.begin(), links.end(), sortByOccuranceDiff);
		}

		// Return the found maximum
		return getMaxVisitableWebpagesInternal(N, links);
	}
};