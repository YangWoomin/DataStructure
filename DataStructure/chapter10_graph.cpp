#include "header.h"

vector<vector<int>> Graph::graph;
int Graph::ALL_MAX_COST = 0;

void graphSimulation() {
	showCommandInGraph();
	string command; cin >> command;
	while (command != "q") {
		if (command == "c") {
			Graph::initailize();
			Graph::createNewGraph();
		}
		else if (command == "s") Graph::showGraph();
		else if (command == "k") {
			Kruskal kru;
			kru.doAlgorithm();
		}
		else if (command == "p") {
			Prim prim;
			prim.doAlgorithm();
		}
		else if (command == "d") {
			Dijkstra dijk;
			dijk.doAlgorithm();
		}
		else if (command == "f") {
			Floyd floyd;
			floyd.doAlgorithm();
		}
		else if (command == "t") {
			TopologicalSort topol;
			topol.doAlgorithm();
		}
		else cout << "Invalid command" << endl;
		showCommandInGraph();
		cin >> command;
	}
}

void showCommandInGraph() {
	cout << "*************************" << endl;
	cout << "* c : create a graph\t*" << endl;
	cout << "* s : show the graph\t*" << endl;
	cout << "* k : kruskal algorithm\t*" << endl;
	cout << "* p : prim algorithm\t*" << endl;
	cout << "* d : dijkstra algorithm*" << endl;
	cout << "* f : floyd algorithm\t*" << endl;
	cout << "* t : topological sort\t*" << endl;
	cout << "* q : quit\t\t*" << endl;
	cout << "*************************" << endl;
}

// Graph
void Graph::initailize() {
	for (vector<vector<int>>::iterator vvi = graph.begin(); vvi != graph.end(); vvi++) (*vvi).clear();
	graph.clear();
	ALL_MAX_COST = 0;
}

void Graph::createNewGraph() {
	cout << "Input the node number(less than 30 and more than 2) : ";
	int nodeNum; cin >> nodeNum;
	if (nodeNum > MAX_NODE_NUM || nodeNum < MIN_NODE_NUM) {
		cout << "Invalid value" << endl;
		return;
	}
	ALL_MAX_COST = MAX_COST * (nodeNum - 1) + 1;
	graph.assign(nodeNum, vector<int>(nodeNum, ALL_MAX_COST));
	for (int i = 0; i < nodeNum; ++i) graph[i][i] = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < nodeNum; ++i) {
		int degree = rand() % (nodeNum - 1) + 1;
		list<int> temp;
		for (int j = 0; j < nodeNum; ++j) {
			if (j == i) continue;
			if (graph[i][j] <= MAX_COST) {
				graph[j][i] = graph[i][j];
				--degree;
				continue;
			}
			temp.insert(temp.end(), j);
		}
		for (int j = 0; j < degree; ++j) {
			int ranNum = rand() % temp.size();
			list<int>::iterator li = temp.begin();
			for (int k = 0; k < ranNum; k++) ++li;
			int ranNum2 = rand() % MAX_COST + 1;
			graph[i][*li] = ranNum2;
			graph[*li][i] = ranNum2;
			temp.erase(li);
		}
	}
}

void Graph::showGraph() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	cout << "form : target node number(cost)" << endl;
	cout.setf(ios::right);
	for (int i = 0; i < graph.size(); ++i) {
		cout << setw(2) << i << " : ";
		for (int j = 0; j < graph[i].size(); ++j)
			if (graph[i][j] <= MAX_COST) cout << setw(2) << j << setw(1) << "(" << setw(3) << graph[i][j] << setw(1) << ") ";
		cout << endl;
	}
	setw(0);
	cout.unsetf(ios::right);
}

// Kruskal
void Kruskal::doAlgorithm() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	typedef struct { int vertex; int target; int cost; } HalfGraph;
	vector<HalfGraph> vh;
	for (int i = 0; i < graph.size(); i++) 
		for (int j = 0; j < graph[i].size(); j++)
			if (j > i && graph[i][j] <= MAX_COST) vh.push_back(HalfGraph{ i, j, graph[i][j] });
	sort(vh.begin(), vh.end(), [](HalfGraph first, HalfGraph second)->bool {return first.cost < second.cost ? true : false; });
	vector<HalfGraph>::iterator hgit = vh.begin();
	vector<set<int>> vertexes;
	for (int i = 0; i < graph.size(); ++i) vertexes.push_back(set<int>{i});
	while (vertexes[0].size() < graph.size()) {
		int index = -1;
		for (int i = 0; i < vertexes.size(); ++i) 
			if (vertexes[i].find(hgit->vertex) != vertexes[i].end()) {index = i; break;}
		for (int i = 0; i < vertexes.size(); ++i) {
			if (vertexes[i].find(hgit->target) != vertexes[i].end()) {
				if (i == index) {
					hgit = vh.erase(hgit);
					break;
				}
				else if (i > index) {
					vertexes[index].insert(vertexes[i].begin(), vertexes[i].end());
					vertexes[i].clear();
				}
				else {
					vertexes[i].insert(vertexes[index].begin(), vertexes[index].end());
					vertexes[index].clear();
				}
				hgit++;
				break;
			}
		}
	}
	cout << "Kruskal result" << endl;
	for (int i = 0; i < graph.size() - 1; i++) 
		cout << "vertex : " << vh[i].vertex << ", target : " << vh[i].target << ", cost : " << vh[i].cost << endl;
}

// Prim
void Prim::doAlgorithm() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	set<int> nodeSet; nodeSet.insert(0);
	vector<int> target, cost; 
	cost.reserve(graph.size() - 1);	target.reserve(graph.size() - 1);
	for (int i = 0; i < graph.size() - 1; ++i) {
		int minCostNode = 0, min = MAX_COST + 1;
		for (set<int>::iterator si = nodeSet.begin(); si != nodeSet.end(); si++) {
			for (int j = 0; j < graph[i].size(); ++j) {
				if (nodeSet.find(j) == nodeSet.end() && graph[*si][j] <= MAX_COST) {
					if (min > graph[*si][j]) {
						min = graph[*si][j];
						minCostNode = j;
					}
				}
			}
		}
		nodeSet.insert(minCostNode);
		target.push_back(minCostNode);
		cost.push_back(min);
	}
	cout << "Prim result : start node 0" << endl;
	for (int i = 0; i < cost.size(); ++i) 
		cout << "target : " << target[i] << ", cost : " << cost[i] << endl;
}

// Dijkstra
void Dijkstra::doAlgorithm() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	cout << "Input the beginning node (0 ~ " << graph.size() - 1 << ") : ";
	int beginNode = 0; cin >> beginNode;
	if (beginNode >= graph.size()) {
		cout << "Invalid node number" << endl;
		return;
	}
	set<int> nodeSet; nodeSet.insert(beginNode);
	vector<int> cost; cost.reserve(graph.size());
	multimap<int, int> costWithNode;
	for (int i = 0; i < graph.size(); ++i) {
		cost.push_back(graph[beginNode][i]);
		if (cost[i] < ALL_MAX_COST && i != beginNode) costWithNode.insert(pair<int, int>(cost[i], i));
	}
	cost[beginNode] = 0;
	for (int i = 0; i < graph.size() - 1; ++i) {
		auto it = costWithNode.begin();
		while (it != costWithNode.end()) {
			auto temp = it++;
			if (nodeSet.find(temp->second) == nodeSet.end()) {
				nodeSet.insert(temp->second);
				for (int j = 0; j < graph.size(); ++j) {
					if (nodeSet.find(j) == nodeSet.end() && cost[j] > cost[temp->second] + graph[temp->second][j]) {
						cost[j] = cost[temp->second] + graph[temp->second][j];
						costWithNode.insert(pair<int, int>(cost[j], j));
					}
				}
				costWithNode.erase(temp);
				break;
			}
			else costWithNode.erase(temp);
		}
	}
	cout << "Dijkstra result (form : node number(minimum cost))" << endl;
	for (int i = 0; i < graph.size(); ++i) cout << i << "(" << cost[i] << ") ";
	cout << endl;
}

// Floyd
void Floyd::doAlgorithm() {
	vector<vector<int>> result(graph);
	for (int i = 0; i < graph.size(); i++) result[i][i] = 0;
	for (int i = 0; i < graph.size(); ++i)
		for (int j = 0; j < graph.size(); ++j)
			for (int k = 0; k < graph.size(); ++k)
				if (result[j][k] > result[j][i] + result[i][k]) result[j][k] = result[j][i] + result[i][k];
	cout << "Floyd result(table)" << endl;
	cout.setf(ios::right); cout << setw(2) << "";
	for (int i = 0; i < graph.size(); ++i) cout << setw(4) << i << " ";
	cout << endl;
	for (int i = 0; i < graph.size(); ++i) {
		cout << setw(2) << i;
		for (int j = 0; j < graph.size(); ++j) cout << setw(4) << result[i][j] << " ";
		cout << endl;
	}
	cout.unsetf(ios::right);
	setw(0);
}

// Topological sort
void TopologicalSort::doAlgorithm() {
	halfGraph.assign(graph.size(), vector<int>(graph.size(), ALL_MAX_COST));
	vector<int> noEntryEdgeNode;
	set<int> nodeSet; for (int i = 0; i < graph.size(); ++i) nodeSet.insert(i);
	for (int i = 0; i < graph.size(); ++i)
		for (int j = 0; j < graph.size(); ++j)
			if (graph[j][i] == 0)
				halfGraph[j][i] = 0;
			else if(graph[j][i] <= MAX_COST && i > j) 
				halfGraph[j][i] = graph[j][i];
	result = 0;
	recursive(nodeSet, noEntryEdgeNode);
	if(result == 0) cout << "No topological sort" << endl;
}

void TopologicalSort::recursive(set<int> nodeSet, vector<int> noEntryEdgeNode) {
	auto sit = nodeSet.begin();
	set<int> checkNode; for (int i = 0; i < noEntryEdgeNode.size(); ++i) checkNode.insert(noEntryEdgeNode[i]);
	while (sit != nodeSet.end()) {
		int i = 0;
		while (i < halfGraph.size()) {
			if (nodeSet.find(i) != nodeSet.end() && halfGraph[i][*sit] != 0 && halfGraph[i][*sit] <= MAX_COST) break;
			else ++i;
		}
		if (i == halfGraph.size() && checkNode.find(*sit) == checkNode.end()) noEntryEdgeNode.push_back(*sit);
		++sit;
	}
	if (noEntryEdgeNode.size() == halfGraph.size() - publicResult.size()) {
		restRecursive(noEntryEdgeNode);
		return;
	}
	for (int i = 0; i < noEntryEdgeNode.size(); ++i) {
		publicResult.push_back(noEntryEdgeNode[i]);
		vector<int> temp1(noEntryEdgeNode); temp1.erase(temp1.begin() + i);
		set<int> temp2(nodeSet); temp2.erase(noEntryEdgeNode[i]);
		recursive(temp2, temp1);
		publicResult.pop_back();
	}
}

void TopologicalSort::restRecursive(vector<int> rest) {
	if (rest.size() == 0) {
		cout << "Result " << ++result << " : ";
		for (int i = 0; i < publicResult.size(); ++i)
			cout << publicResult[i] << " ";
		cout << endl;
		return;
	}
	for (int i = 0; i < rest.size(); ++i) {
		publicResult.push_back(rest[i]);
		vector<int> temp(rest); temp.erase(temp.begin() + i);
		restRecursive(temp);
		publicResult.pop_back();
	}
}