# Meeting Rooms

## Problem

Given an array of meeting time intervals, return whether one person can attend
all meetings. Two meetings do not overlap when one starts exactly when the
other ends.

## Approach

Sort the intervals by start time and then by end time. After sorting, compare
every adjacent pair. The meetings overlap if the previous interval ends after
the next interval starts.

- Time complexity: `O(intervals.size() * log(intervals.size()))`
- Additional space: `O(log(intervals.size()))` for the sorting stack
