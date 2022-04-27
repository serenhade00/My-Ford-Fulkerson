# 🚰 My-Ford-Fulkerson Algorithm 🚰


## 개요
***
<br>

* `Ford-Fulkerson` 알고리즘의 정의와 목적 + 기초 배경지식
* `Ford-Fulkerson` 알고리즘 실제 구현 프로그램 분석
    * 코드 동작 방식
    * 코드 실행 결과
    * 코드 성능 분석
* `Ford-Fulkerson` 프로그램의 한계 및 개선점
* `Ford-Fulkerson` vs `Edmonds-Karp Algorithm`
* 결론

## Ford-Fulkerson 알고리즘에 관하여
***

**Ford-Fulkerson** 알고리즘은 도대체 무엇이며, 언제 사용되는 알고리즘인가? 

일단 이 알고리즘은 **그리디(Greedy)** 또는 **다이나믹 프로그래밍(DP)** 처럼 다양한 문제를 푸는데에 통용되는 알고리즘 **일반화된 기법(Technique)** 이라기보다는, **특정 상황**에 적용되는 알고리즘이다. 물론, 꼭 **"특정 상황"** 에만 쓴다는건 아니지만 비교적 사용 목적이 디테일한 알고리즘이다.

그렇다면, 여기서 말하는 **특정 상황**은 무엇인가?
* *Network Flow*
* *Maximum Flow*

### **Network Flow / Maximum Flow**
***

**정의:** 
> 유량 그래프에서 <u>시작점으로 정의된 정점</u>에서 <u>도착점으로 정의된 정점</u>까지 최대 얼마만큼의 **유량(Flow)** 이 지나갈 수 있는지 구하는 문제

* 유량 그래프의 특성:
    * 간선의 가중치가 정점에서 정점으로 보낼 수 있는 최대 유량을 의미하는 그래프
    * 방향 그래프(directed graph)

**관련 용어:**

* Source: 시작점
* Sink: 도착점
* Capacity: 용량 (간선에서 소화 가능한 최대 양 or 값)
* Flow: 유량 (간선에서 용량을 점유하고 있는, 사용하고있는 양 or 값)
* ![first_img](https://latex.codecogs.com/png.latex?c%28u%2Cv%29): 정점 a 에서 b로, 소화 가능한(남은) 용량 값
* ![second_img](https://latex.codecogs.com/png.latex?f%28u%2Cv%29): 정점 a 에서 b로, 사용하고 있는(쓴) 유량 값

=> 출발점에서 물을 흘려보내 도착지점에 가장 많은 물을 흘려보낼 수 있는 경우의 결과값을

![first_img](https://latex.codecogs.com/png.latex?c%28u%2Cv%29)

$x+1$


