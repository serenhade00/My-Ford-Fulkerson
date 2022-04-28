#include <bits/stdc++.h>

#define MAX 100         // 그래프 인접행렬 최대 인덱스
#define INF 99999999    // 최대 유량 갱신을 위한 최초 비교값

using namespace std;

int n;                                                    // 그래프의 노드와 간선 관계 가짓수
int c[MAX][MAX], f[MAX][MAX], vis[MAX];                   // c = 용량 배열 f = 유량 배열 vis = 탐색 위한 배열
int adj[MAX][MAX];                                        // 그래프 인접행렬

int dfs(int a, int E, int flow)                           // a = 현재 노드 , E = 도착지 , flow = 현재 최대 유량
{
	if(vis[a])                                            // 이미 방문한 곳이면 return 0
		return 0;
	vis[a] = 1;                                           // 방문하지않은 노드이면 방문한것으로 갱신
	
	if(a == E)                                            // 현재 노드가 도착지에 도달하면 현재 최대 유량 return
		return flow;
	
	for(int i=1; i<=26; i++)                              // A부터 Z로 이름 지어진 노드를 받았기에 인접행렬의 인덱스는 1부터 26
	{
		if(!adj[a][i] || vis[i])                          // 간선이 없거나 이미 방문된 노드면 skip
			continue;
		int cur_flow = c[a][i] - f[a][i];                 // 잔여 용량 계산
		if(cur_flow <= 0)                                 // 잔여 용량이 0이하면 그 경로는 갈 수 없으므로 skip
			continue;
		
		int result = dfs(i, E, min(flow, cur_flow));      // dfs로 탐색하여 최대 유량 result에 저장
		if(result)                                        // result값이 양의 정수로 존재하면
		{
			f[a][i] += result;                            // 경로의 양방향으로는 유량 + 갱신
			f[i][a] -= result;                            // 경로의 음방향으로는 유량 - 갱신
			adj[i][a] = 1;                                // 역간선 생성
			
			return result;                                // T에 도달하는 유량 return
		}
	}
	return 0;
}

int max_flow(int S, int E)                                // 탐색 가능한 경로가 더 없을때까지 돌리는 함수, S = 시작지, E = 도착지 
{
	int result = 0;                                       // 최종 결과
	while(1)
	{
		memset(vis, 0, sizeof(vis));                      // 새로운 매번의 탐색마다 vis값 초기화
		int flow = dfs(S, E, INF);                        // 한번의 탐색마다 T에 도달하는 유량 반환
		if(!flow)
			break;                                        // 더이상 탐색할 수 없는, 즉 최대 유량 값이 0이 나오면 종료
		result += flow;                                   // T에 도달하는 유량 갱신
	}
	return result;                                        // 최종 결과 출력
}

int main(void)
{
	cin >> n;                                             // 그래프 정보 가짓수 입력
	
	for(int i=0; i<n; i++)
	{
		char u, v;                                        // 그래프 노드 u -> v
		int cap;                                          // 용량
		cin >> u >> v >> cap;                            
		c[u-64][v-64] = cap;                              // 용량 배열 갱신
		adj[u-64][v-64] = 1;                              // 간선 인접행렬 갱신
	}
	
	cout << max_flow(1, 26);                              // 최종 결과 출력
}