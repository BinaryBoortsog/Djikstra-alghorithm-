#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

void dijkstra(int n, const vector<vector<pair<int, int>>> &edges)
{
    // 각 정점까지의 최단 거리를 저장할 벡터, 초기값은 무한대
    vector<int> distances(n, numeric_limits<int>::max());
    distances[0] = 0; // 시작 정점(0번 정점)의 거리는 0으로 설정

    // 우선순위 큐, pair<int, int>에서 첫 번째 요소는 거리, 두 번째는 정점
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // 시작 정점을 큐에 삽입

    while (!pq.empty())
    {
        // 현재 정점과 그 정점까지의 거리를 큐에서 꺼냄
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        // 만약 현재 거리가 이미 기록된 거리보다 크면 처리하지 않음
        if (current_distance > distances[current_vertex])
        {
            continue;
        }

        // 현재 정점과 연결된 모든 이웃 정점들에 대해 처리
        for (const auto &edge : edges[current_vertex])
        {
            int neighbor = edge.first; // 이웃 정점
            int weight = edge.second;  // 간선의 가중치
            int distance = current_distance + weight; // 이웃 정점까지의 새로운 거리

            // 만약 새로운 거리가 기존 거리보다 짧으면 갱신하고 큐에 삽입
            if (distance < distances[neighbor])
            {
                distances[neighbor] = distance;
                pq.push({distance, neighbor});
            }
        }
    }

    // 0번 정점을 제외한 다른 모든 정점까지의 최단 거리를 출력
    for (int i = 1; i < n; ++i)
    {
        if (distances[i] == numeric_limits<int>::max()) // 경로가 없는 경우
        {
            cout << i << " INF" << endl; // 무한대 표시
        }
        else
        {
            cout << i << " " << distances[i] << endl; // 최단 거리 출력
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m; // 정점의 개수 n과 간선의 개수 m을 입력받음

    // 그래프를 인접 리스트로 표현, 각 정점은 연결된 정점과 가중치로 이루어진 쌍(pair)을 가짐
    vector<vector<pair<int, int>>> edges(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w; // 간선 정보 입력 (정점 u에서 v로 가는 가중치 w)
        edges[u].emplace_back(v, w); // 정점 u에서 v로 가는 간선 추가
    }

    // 다익스트라 알고리즘 실행
    dijkstra(n, edges);
    return 0;
}
