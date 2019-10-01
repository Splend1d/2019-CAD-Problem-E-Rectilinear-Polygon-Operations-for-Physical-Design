More details of this problem could be found on http://iccad-contest.org/2019/tw/problems.html

I used boost library's internal function to do basic operations such as merge, clip, split horizontal, and split vertical.
For optimize splitting, I developed the following algorithm:
1. Store the nodes of the polygon
2. Perform Split_V and Split_H
3. Choose the one that has fewer rectangles, and use fewer rectangles, and use the splitted data as the base set.
4. For each of the rectangle in the base set, if all four vertices are are original nodes of the polygon, then put the rectangle in set A, if there exist extra vertices(which lies on an edge of the original polygon but not a node), store the rectangle in set B
5. Remerge the polygon in set B, and perforn split V and split H, take the minimum of the two, and add them to set A.
6. Output set A
* If the polygon has edges <= 6, we perform split H on it because it is trivial.

