# Meeting Rooms II

## Problem

Given an array of meeting time intervals, return the minimum number of meeting
rooms required to hold all meetings. A room can be reused when one meeting
ends exactly when another starts.

## Approach

Sort the intervals by start time and keep the end times of all active meetings
in a min-heap. Before adding a meeting, remove every meeting that has already
ended. The maximum heap size is the number of rooms required.

- Time complexity: `O(intervals.size() * log(intervals.size()))`
- Additional space: `O(intervals.size())`
