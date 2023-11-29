#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <iostream>
#include "structs.h"
using namespace std; 

// To find the closest pair of points
float sweepLine(vector<Point> coordinates)
{
    int n = coordinates.size(); 
    int i;
    // Vector pair to store points on plane
    vector<pair<float, float> > v;
    for (i = 0; i < n; i++)
        v.push_back({ coordinates[i].x,
                      coordinates[i].y });
 
    // Sort them according to their
    // x-coordinates
    sort(v.begin(), v.end());
 
    // Minimum distance b/w points
    // seen so far
    float d = INT_MAX;
 
    // Keeping the points in
    // increasing order
    set<pair<float, float> > st;
    st.insert({ v[0].first, v[0].second });
 
    for (i = 1; i < n; i++) {
        auto l = st.lower_bound(
            { v[i].first - d, v[i].second - d });
        auto r = st.upper_bound(
            { v[i].first, v[i].second + d });
        if (l == st.end())
            continue;
 
        for (auto p = l; p != r; p++) {
            pair<float, float> val = *p;
            float dis = (v[i].first - val.first)
                           * (v[i].first - val.first)
                       + (v[i].second - val.second)
                             * (v[i].second - val.second);
 
            // Updating the minimum
            // distance dis
            if (d > dis)
                d = dis;
        }
        st.insert({ v[i].first, v[i].second });
    }
 
    return d;
}