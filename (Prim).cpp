#include <iostream>            // 표준 입력 출력 라이브러리
#include <vector>              // 벡터를 사용하기 위한 라이브러리
#include <queue>               // 우선순위 큐를 사용하기 위한 라이브러리
#include <utility>             // std::pair를 사용하기 위한 라이브러리
using namespace std;

void prim(int n, const vector<vector<pair<int, int>>> &edges)
{
    // MST에 포함 여부를 추적하는 벡터
    vector<bool> inMST(n, false);

    // 우선순위 큐를 사용하여 간선들을 관리, pair<int, pair<int, int>> 형식
    // 첫 번째 요소는 간선의 가중치, 두 번째는 {u, v}로 연결된 두 정점
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // 0번 정점을 MST에 포함시키고, 이 정점과 연결된 모든 간선을 큐에 추가
    inMST[0] = true;
    for (const auto &edge : edges[0])
    {
        pq.push({edge.second, {0, edge.first}});
    }

    // 큐가 비어 있지 않은 동안 계속해서 최소 가중치 간선을 선택
    while (!pq.empty())
    {
        // 큐에서 가장 가중치가 작은 간선을 꺼냄
        int weight = pq.top().first;        // 간선의 가중치
        int u = pq.top().second.first;      // 간선의 출발 정점
        int v = pq.top().second.second;     // 간선의 도착 정점
        pq.pop();                           // 선택한 간선 제거

        // 이미 도착 정점이 MST에 포함되어 있으면 건너뜀
        if (inMST[v])
        {
            continue;
        }

        // 선택한 간선을 출력 (출발 정점 u, 도착 정점 v, 가중치 weight)
        cout << u << " " << v << " " << weight << endl;

        // 도착 정점을 MST에 포함
        inMST[v] = true;

        // 도착 정점에서 연결된 간선들 중 MST에 포함되지 않은 정점과 연결된 간선을 큐에 추가
        for (const auto &edge : edges[v])
        {
            if (!inMST[edge.first])
            {
                pq.push({edge.second, {v, edge.first}});
            }
        }
    }
}

int main()
{
    // 정점의 개수 n, 간선의 개수 m 입력받기
    int n, m;
    cin >> n >> m;

    // 그래프를 저장할 인접 리스트 edges를 선언
    vector<vector<pair<int, int>>> edges(n);

    // 간선 정보 입력받기
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;               // u에서 v로 가는 가중치 w의 간선을 입력받음
        edges[u].emplace_back(v, w);      // u 정점에 연결된 간선을 리스트에 추가
        edges[v].emplace_back(u, w);      // 양방향 그래프이므로 v에도 같은 간선 추가
    }

    // 프림 알고리즘 실행
    prim(n, edges);

    return 0;
}
