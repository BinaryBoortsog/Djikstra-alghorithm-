class UnionFind:
    def __init__(self, n):
        # 각 정점의 부모를 자기 자신으로 초기화
        self.parent = list(range(n))
        # 트리의 높이(rank)를 추적하기 위한 배열
        self.rank = [0] * n

    def find(self, u):
        # 경로 압축(Path compression) 기법 사용
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        # 두 정점 u와 v의 루트 노드를 찾음
        root_u = self.find(u)
        root_v = self.find(v)
        
        if root_u != root_v:
            # 트리의 높이를 기준으로 Union by Rank 기법 사용
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1
            return True  # Union 성공
        return False  # 이미 같은 집합에 있음

def kruskal(n, edges):
    # 간선을 가중치 기준으로 정렬
    edges.sort(key=lambda x: x[2])
    
    # 유니온-파인드 구조체 초기화
    uf = UnionFind(n)
    mst_edges = []  # MST에 포함될 간선 리스트
    total_weight = 0  # MST의 총 가중치

    # 간선을 하나씩 처리하여 사이클이 없는 경우 MST에 추가
    for u, v, w in edges:
        if uf.union(u, v):
            mst_edges.append((u, v, w))
            total_weight += w

    return mst_edges, total_weight

# 입력받기
n, m = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(m)]

# 최소 신장 트리 찾기
mst_edges, total_weight = kruskal(n, edges)

# 출력하기
for u, v, w in mst_edges:
    print(u, v, w)
print(total_weight)
