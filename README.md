# 🚰 My-Ford-Fulkerson Algorithm 🚰


## 개요
***
<br>

* `Ford-Fulkerson` 알고리즘의 정의와 목적 + 기초 배경지식
* `Ford-Fulkerson` vs `Edmonds-Karp Algorithm`
* `Ford-Fulkerson` 알고리즘 실제 구현 프로그램 분석
    * 코드 동작 방식
    * 코드 실행 결과
    * 코드 성능 분석
* `Ford-Fulkerson` 프로그램의 한계 및 개선점
* 결론

## Ford-Fulkerson 알고리즘에 관하여
***

**Ford-Fulkerson** 알고리즘은 도대체 무엇이며, 언제 사용되는 알고리즘인가? 

일단 이 알고리즘은 **그리디(Greedy)** 또는 **다이나믹 프로그래밍(DP)** 처럼 다양한 문제를 푸는데에 통용되는 알고리즘 **일반화된 기법(Technique)** 이라기보다는, **특정 상황**에 적용되는 알고리즘이다. 물론, 꼭 **"특정 상황"** 에만 쓴다는건 아니지만 비교적 사용 목적이 디테일한 알고리즘이다.

그렇다면, 여기서 말하는 **특정 상황**은 무엇인가?
* *Network Flow*
* *Maximum Flow*

### **Network Flow / Maximum Flow**

**정의:** 
> 유량 그래프에서 <u>시작점으로 정의된 정점</u>에서 <u>도착점으로 정의된 정점</u>까지 최대 얼마만큼의 **유량(Flow)** 이 지나갈 수 있는지 구하는 문제

ex) 출발점에서 물을 흘려보내 도착지점에 가장 많은 물을 흘려보낼 수 있는 경우의 결과값 도출

* 유량 그래프의 특성:
    * 간선의 가중치가 정점에서 정점으로 보낼 수 있는 최대 유량을 의미하는 그래프
    * 방향 그래프(directed graph)

**관련 용어:**

| 값 | 의미 |
|--- |---|
| `Source` | 시작점 | 
| `Sink` | 도착점 |  
| `Capacity` | 용량 (간선에서 감당 가능한 최대 양) |  
| `Flow` | 유량 (간선에서 용량을 점유하고 있는, 즉 이미 사용중인 양) |
| `C(u, v)` | 정점 u 에서 v로, 현재 감당 가능한(남은) 용량 값 |  
| `F(u, v)` | 정점 u 에서 v로, 이미 사용하고 있는(쓴) 유량 값 |    

**제약 조건:**

1. **Capacity constraints - 용량 제한**
    - f(u, v) <= c(u, v) 
    - 유량은 용량을 초과할 수 없다. 

    ☞ 용량이 노드에서 감당 가능한 최댓값이므로 당연히 그 노드를 통과하는 유량은 이보다 작거나 같을 수밖에 없다.

2. **Flow conservation - 유량 보존**
    - Σf(u1, v1) = Σf(v1, u2)
    - 노드에 들어오는 유량 총합 = 노드에서 나가는 유량 총합이다.

    ☞ 해답을 구하는데 있어서 어느 한 지점에 유량을 보존하면 안되기에(최대 유량을 구하는데 중간에 유량을 남겨두면 손해), 들어오는 유량과 나가는 유량의 총합은 같다.
3. **Skew symmetry - 유량 대칭**
    - f(u, v) = -f(v, u)
    - 노드에서 흘러나가는 유량 = -(그 노드로 흘러드는 유량)
    - **알고리즘의 주요 핵심 특성이다.** 

    ☞ 노드 u에서 노드 v로 x만큼의 유량이 흐른다고 가정하면, 그 반대 방향으로는 -x만큼의 유량이 흐른다고 생각한다. 즉 가상의 간선이 존재한다고 생각한다. 

    ☞ 이 가상의 간선은 잔여 간선 또는 역간선이라고 함.

 ## **Ford-Fulkerson vs Edmonds-Karp**
 ***


 결국 이런 Network Flow 문제를 풀기 위한 알고리즘이 바로 **Ford-Fulkerson**인것이다. 또한 이와 비슷하지만 조금 다른 기법을 사용하는 **Edmonds-Karp** 알고리즘이 존재한다. 두 알고리즘의 진행 방식은 이렇다.

 1. Source에서 Sink로 가는 경로를 찾는다. **증가경로** 또는 **augmenting path**로 불린다. 이때 주의할점은 반드시 여유 용량이 남아 있어야 한다는것이다. 즉 경로상의 모든 노드 및 간선에서 `c(u, v)-f(u, v) > 0` 가 성립하여야 한다. 그래야지만 그 경로로 유량이 흐를 수 있는 여지가 있기 때문이다.

 2. 찾아낸 경로에 보낼수 있는 최대 유량을 찾는다. 이때 이 "최대 유량"은 경로에 남은 용량 중 최솟값이다. 

 > "최대 유량"은 경로에 남은 용량 중 최솟값

이 문장을 증명해보겠다. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/example.jpg?raw=true" width="500" height ="300" />

<br>
위의 그림에서 Cn은 각 수로(간선)을 지날 수 있는 물의 용량이다. 아무리 큰 용량(그림에서는 8이 최대)을 가진 노드가 있어도 결국 각 노드는 자신의 수용량 Cn이상의 물은 통과시킬 수 없다. 따라서 특정 경로에서 전체 수로를 통과할 수 있는 물의 양은 경로상에 있는 최소 용량(그림에서 2가 최소)이다.

<br>

3. 찾아낸 경로에, 찾아낸 최대 유량을 흘려보낸다. 
    - 전체 경로에 f(u, v) += flow.

    ex) 경로 a-b-c-d

    f(a, b) += flow, f(b, c) += flow, f(c, d) += flow 을 한다.

    동시에 '유량 대칭' 조건에 따라 역방향 역시 flow을 음수값으로 설정한다.

    f(b, a) -= flow, f(c, b) -= flow, f(d, c) -= flow 을 한다.

4. 더이상 **augmenting path**가 없을때까지 1~3의 과정을 반복한다. 

그렇다면, 첫번째 과정인 경로를 찾는건 어떻게 하는가? <u>사실 `Ford-Fulkerson`과 `Edmonds-Karp` 알고리즘의 차이가 여기서 갈린다.</u>

| 종류 | 탐색 기법 |
|--- |---|
| `Ford-Fulkerson` | **DFS** | 
| `Edmonds-Karp` | **BFS** | 

*DFS(깊이 우선 탐색)*

- 말 그대로 깊이를 우선시해 탐색한다. 즉 어느 한쪽 방향으로 갈 수 있을때까지 쭉 간다음, 한칸씩 백트래킹(backtracking)하며 갈 수 있는 또 다른 방향이 존재한다면 그 노드를 우선 방문하고, 이를 반복한다.

DFS 코드
```c++
void dfs(int node, int cur)
{
	vis[cur] = 1;
	cout << cur << ' ';
	for(int i=1; i<=node; i++)
	{
		if(!vis[i] && graph[cur][i])
		{
			dfs(node, i);
		}
	}
}
```
구현은 이렇게 했다.

* `node`는 정점의 개수, `cur`은 현재 방문한 노드이다. 즉 시작점부터 시작해 간선으로 연결된 노드 중 가장 숫자가 낮은 노드(i)부터 방문한다. 그 다음 반복문에서는 방금 방문한(i)가 cur이 되어 이 노드에 연결된 노드를 방문한다.
* 이를 반복하다보면 결국 더이상 방문할 곳이 없는 경우의 수를 가진 최종 노드를 만나 return 하고, 이 전에 실행된 dfs 함수는 방금 전 노드를 가리키므로 그 노드부터 또 탐색을 시작하는것이다. 

*BFS(너비 우선 탐색)*

- DFS와 달리 너비를 우선시한다. 너비가 우선이라는 의미는, DFS는 어느 한쪽 끝까지 갔다가 돌아오는걸 반복하는 반면 BFS는 시작점으로부터 사방으로 점점 뻗어나가 모든 방향을 장악해나간다.

BFS 코드
```c++
void bfs(int node, int cur)
{
	queue<int> Q;
	
	vis[cur] = 1;
	cout << cur << ' ';
	Q.push(cur);
	while(!Q.empty())
	{
		int c = Q.front();
		Q.pop();
		for(int i=1; i<=node; i++)
		{
			if(vis[i] || graph[c][i]==0)
				continue;
			vis[i] = 1;
			cout << i << ' ';
			Q.push(i);
		}
		
	}
}
```

구현은 이렇게 했다.
* BFS 특성상 시작점에 가까운 순서로 방문되기에 먼저 방문한 노드에 연결된 노드를 먼저 봐야하므로 선입선출(FIFO) 구조인 큐(Queue)를 이용했다. 
* 노드에 연결된 모든 정점을 큐에 넣고, 방문 처리한다. 그 다음 큐에서 원소를 하나씩 꺼내보면서(pop) 그 노드에 연결된 노드를 방문처리하고, 큐에 집어넣고를 반복한다.

이 탐색 알고리즘의 차이로 인해 두 알고리즘의 시간복잡도가 달라진다. 따라서 어느 한쪽이 무조건 좋다기보다는 상황에 맞춰서 잘 선택해야한다. 

### **Ford-Fulkerson 도식화**

Step-by-Step으로 한번 알고리즘을 분석해보자. 

다음과 같은 유량 그래프가 있다고 하자. **Ford-Fulkerson** 알고리즘은 **역간선**이 핵심인데, 중요성을 알아보기 위해 역간선 없이 그냥 기존 경로만을 사용해 알고리즘을 돌려보자. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow1.png?raw=true" width="500" height ="300" />

<br>

1. **증가경로(augmenting path)** 를 DFS로 찾는다. 
* 원래는 첫 경로가 S -> A -> D -> T가 되겠지만 역간선의 중요성을 설명하기 위해 S -> A -> E -> T의 경로를 찾았다고 하자. 경로를 찾을때의 주의점인 "c(u, v)-f(u, v) > 0" 이 경로의 모든 정점에 대해 만족되므로 경로를 채택한다. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow2.png?raw=true" width="500" height ="300" />

2. 경로에 보낼 수 있는 **최대 유량**을 찾는다. 
* S → A → E → T 에서 각각의 남은 capacity는 아래와 같다. (남은 용량 c(u, v) - f(u, v))

        S → A: c(s, a) - f(s, a) = 3 - 0 = 3
        A → E: c(a, e) - f(a, e) = 3 - 0 = 3
        E → T: c(e, t) - f(e, t) = 5 - 0 = 5

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow3.png?raw=true" width="500" height ="300" />

위 3가지 경우에서 최솟값은 3이므로 최대 유량은 3이다.


3. 경로에 찾아낸 **최대 유량**을 실제 흘려보낸다.

S → A → E → T 경로에 2번 과정에서 찾은 최솟값 3을 사용 유량에 모두 더한다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow4.png?raw=true" width="500" height ="300" />

<br>
현재 T까지 도달한 Total유량은 3이다.

이 과정을 더 이상 경로가 없을때까지 반복하면 된다. 

다음 경로로는 S -> B -> E -> T 를 얻는다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow5.png?raw=true" width="500" height ="300" />

현재 T까지 도달한 Total유량은 5이다.

다음 경로는 S -> C -> F -> E -> T 이지만 E -> T의 잔여 용량이 남아 있지 않으므로 이 경로는 사용할 수 없어 스킵한다.

다음으로 S -> C -> F -> T 경로를 얻고, 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow6.png?raw=true" width="500" height ="300" />

현재 T까지 도달한 Total유량은 9이다.
모든 증가 경로를 탐색했으므로 알고리즘은 종료된다.

즉 얻은 정답은 9이다. 하지만 과연 이것이 정답일까?

다음 그래프 상태를 보자. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow7.png?raw=true" width="500" height ="300" />

<br>

이와 같이 유량이 분배되면 최종 정답은 10이다. 실제 정답과 직접 구한 최종 그래프를 비교해보자.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow9.png?raw=true" width="550" height ="250" />

> 즉, A -> E 부분에서 1을 빼서 A -> D로 분배하면 D -> T 로 가는 1만큼의 양이 증가하고, E의 잔여 용량이 1만큼 남았으므로 S -> C -> F -> E -> T를 통해 1을 보충해주어 정답이 10으로 유도한다.

**결국, 이렇게 오답이 발생하는 이유는 한번 흐른 유량은 다시 돌아와서 재분배를 할 수 없기에 더 나은 경로를 개선할 여지가 없는것이다.** 이를 가능하게 만들기 위해 **역간선**을 도입한다.

이제, 역간선이 생겼다고 가정하고 알고리즘을 재진행한다. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow10.png?raw=true" width="500" height ="300" />

다음과 같이 역간선이 생기면 경로 S -> C -> F -> E -> A -> D를 찾을 수 있다. 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow11.png?raw=true" width="500" height ="300" />

여기서 아까와 같은 과정을 반복하면, 

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow12.png?raw=true" width="500" height ="300" />

* 경로에 유량을 흘릴때, 정방향은 유량을 + 하고, 역방향은 - 한다.
* flow을 정, 역방향을 흘림으로 해서, 기존 A → E가 2로 줄어들고, 1만큼 남은 유량이 A → D → T 로 가는것을 확인했다.

이 다음은 역간선이 생겨도 더 이상의 증가경로가 존재하지 않는다.

그러므로, 최종 답인 10을 도출한다.

## Ford-Fulkerson 프로그램 분석
***

### **코드 분석**

`My-Ford-Fulkerson` 프로그램은 2개의 사용자 정의 함수와 main 함수로 구성했다.

사용자 정의 함수는 다음과 같다.
* `dfs`, 증가경로 탐색, 최대유량 탐색, 유량 갱신, 역간선 생성
* `max_flow`, 매 탐색에 대해 도착지로 흘러드는 유량을 총 갱신하여 정답 도출

**<u>각 코드가 어떤 기능을 가지고 무슨 역할을 수행하는지는 소스 코드에 주석을 자세하게 달아놓았으니 참조바란다.</u>**

### **실행 결과**

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/test.jpg?raw=true" width="500" height ="300" />

* 코드의 일반성을 위해 시작점을 A점으로 잡고, 종료점을 Z점으로 잡았다. 즉 예시로 들었던 그래프에 대입하면 A가 S이고, Z가 T인걸 제외하고 나머지 간선과 용량은 동일하게 입력으로 집어넣은 테스트 결과이다. 

* 10으로 결과가 잘 출력되는걸 볼 수 있다.

### **성능 분석**

* 시간복잡도
    - `DFS` 함수에서는 DFS를 할때 도착지까지 쭉 갔다가 **(O(n))**, backtracking하며 다시 시작점까지 돌아오며 경로를 탐색하고 **(O(n))**, 다시 새로운 노드로 탐색을 시작하는 과정을 반복하기에, 시간복잡도는 **O(n^2)**. 어차피 최대 유량을 찾고 역간선을 만드는 과정은 상수시간만에 찾을 수 있기에 무시해도된다. 
    - `max_flow` 함수에서는 `vis`배열을 `memset`함수로 초기화하고 **(O(n))**, `DFS`함수에서 반환해오는 유량값을 더하고만 있으므로 **(O(1))** 총 시간복잡도는 **O(n)** 이다.

* 최악의 상황에는?

이번엔 알고리즘 자체의 시간복잡도를 분석해보자.

다음과 같은 그래프가 있을시, 
<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow-ford-fulkerson13.png?raw=true" width="500" height ="300" />

DFS의 성질로 인해 A -> B -> C -> D의 경로를 찾는다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow-ford-fulkerson14.png?raw=true" width="500" height ="300" />

최대 유량값인 1을 흘려보낸다. 이때 C -> B로 향하는 -1/0의 역간선이 생긴다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/network-flow-ford-fulkerson15.png?raw=true" width="500" height ="300" />

따라서 다음 경로는 A -> C -> B -> D이고, 최대 유량인 1이 경로대로 흐른다. 이때 다시 역간선 B -> C가 1/1에서 0/1로 변한다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/networkflow-ford-fulkerson16.png?raw=true" width="500" height ="300" />

그럼 결국 루프가 1000번 돌때까지 이 두가지의 경로만을 반복한다. 매우 비효율적인 셈이다. 즉, 알고리즘의 시간복잡도는 노드의 개수 V와 간선의 개수 E의 합에 최대 유량(예시에서는 1000) F의 곱인 **O(V+E)*F**이다.

이에 반해 **BFS**를 사용하는 `Edmonds-Karp` 알고리즘은 어떨까?

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/17.png?raw=true" width="500" height ="300" />

BFS를 통해 탐색하면 처음 얻는 경로는 S -> A -> T이고, 그 다음은 S -> B -> T이다. 이 두 경로를 반복하며 의미없는 동선낭비 없이 
`Fork-Fulkerson`보다 빠르게 답을 구해낸다.

<img src = "https://github.com/serenhade00/My-Ford-Fulkerson/blob/main/image/18.png?raw=true" width="500" height ="300" />

즉, `Edmonds-Karp` 알고리즘은 유량의 양보다는 간선 Edge의 개수가 많을수록 반복횟수가 많아지므로 E의 영향을 많이 받는다. 시간복잡도는 **O(VE^2)** 이다.

## 한계 및 개선점
***

- 이 프로그램은 다소 정적인면이 존재한다. 예시로 설정한 그래프의 결과값을 정확히 비교하기 위해 임의로 시작점과 도착점을 지정해주고 실행한 프로그램이기에 Network Flow의 정의랑은 살짝 어긋난다. 이 점을 개선하면 좀 더 동적인 프로그램이 될것이다.

- 그래프와 DFS를 인접행렬을 통해 구현했는데, 이는 **O(n^2)** 의 시간복잡도를 가졌었다. 이를 인접리스트나 다른 방법을 이용해 구현하면 아무래도 모든 원소를 비교하는 배열보다는 좀 더 시간을 단축시킬 수 있을것이다.

- 문제의 조건이 좀 더 다양해진다면 프로그램은 제대로 동작하지 못한다. 예를 들어 노드 사이에 중복된 간선이 존재하거나, 애초에 양방향인 간선이 동시에 주어진다거나 하면 프로그램을 올바른 답을 도출하지 못할것이다. 이런 조건들을 좀 더 고려할 필요가 있다.

## 결론
***

- `Ford-Fulkerson` 알고리즘은 `Network Flow` 문제를 해결하기 위한 알고리즘이다.

- `Ford-Fulkerson` 알고리즘의 성격은 Greedy하다. 왜냐하면 잔여 용량이 남아있을시 최대한 그 용량까지 이용하여 탐욕적이게 최댓값을 갱신해 나가기 때문이다. 

- `Ford-Fulkerson` 과 `Edmonds-Karp` 알고리즘은 탐색 기법에서 차이가 나고, 상황에 따라 알고리즘을 잘 선택해야한다. 

| 알고리즘 종류 | 탐색 기법 | 시간복잡도 | 채택 기준
|---|---|---|---|
| `Ford-Fulkerson` | DFS | **O(V+E)F** | Flow가 적을때
| `Edmonds-Karp` | BFS | **O(VE^2)** | Edge가 적을때

<br>

<p align="center">Copyrightⓒ. 2022. By Seonghwan Shin. </p>
<p align="center">All Rights Reserved.</p>
<p align="center">-The End-</p>
