/*
 * 841. 钥匙和房间	url: https://leetcode.cn/problems/keys-and-rooms/
 *
 * 题目描述：有 n 个房间，房间按从 0 到 n - 1 编号。最初，除 0 号房间外的其余所有房间都被锁住。
 * 你的目标是进入所有的房间。然而，你不能在没有获得钥匙的时候进入锁住的房间。
 *
 * 当你进入一个房间，你可能会在里面找到一套不同的钥匙，每把钥匙上都有对应的房间号，即表示钥匙可以打
 * 开的房间。你可以拿上所有钥匙去解锁其他房间。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution
{
 public:
	bool canVisitAllRooms(vector<vector<int>>& rooms)
	{
		vector<bool> visited(rooms.size(), false); // 记录遍历过的房间
		int count = 0;    // 记录遍历了的房间数量
		queue<int> qu;    // 记录下一个 且 没有被访问的房间

		// 遍历 0 号房间
		qu.push(0);
		visited[0] = true;
		count++;

		while (!qu.empty())
		{
			int cur_room = qu.front();
			qu.pop();

			for (int i = 0; i < rooms[cur_room].size(); i++)
			{
				// 每遍历到一个没有去过的房间 count 加一
				if (!visited[rooms[cur_room][i]])
				{
					qu.push(rooms[cur_room][i]);
					visited[rooms[cur_room][i]] = true;
					count++;
				}
			}
		}

		return rooms.size() == count;
	}
};

class Solution2
{
 private:
	// 深搜
	void dfs(vector<vector<int>>& rooms, vector<bool>& visited, int cur_room)
	{
		if (visited[cur_room]) return;

		visited[cur_room] = true;
		for (int i = 0; i < rooms[cur_room].size(); i++)
		{
			dfs(rooms, visited, rooms[cur_room][i]);
		}
	}

 public:
	bool canVisitAllRooms(vector<vector<int>>& rooms)
	{
		vector<bool> visited(rooms.size(), false);
		dfs(rooms, visited, 0);

		for (int i = 0; i < visited.size(); i++)
		{
			if (!visited[i]) return false;
		}
		return true;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> rooms;

	{
		rooms = {{ 1 }, { 2 }, { 3 }, {}};
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.canVisitAllRooms(rooms) << endl;
	}

	{
		rooms = {{ 1, 3 }, { 3, 0, 1 }, { 2 }, { 0 }};
		cout << "exp2 (false): " << endl;
		cout << "result: " << solution.canVisitAllRooms(rooms) << endl;
	}
}
