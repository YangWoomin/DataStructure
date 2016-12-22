#include "header.h"

vector<map<int, int>> Graph::graph;

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
	cout << "* q : quit\t\t*" << endl;
	cout << "*************************" << endl;
}

// Graph
void Graph::initailize() {
	for (int i = 0; i < graph.size(); i++) {
		graph.at(i).clear();
	}
	graph.clear();
}

void Graph::createNewGraph() {
	cout << "Input the node number(less than 30 and more than 2) : ";
	int nodeNum; cin >> nodeNum;
	if (nodeNum > 31 || nodeNum < 2) {
		cout << "Invalid value" << endl;
		return;
	}
	graph.reserve(nodeNum + 1); map<int, int> init{};
	for (int i = 0; i <= nodeNum; i++) graph.push_back(init);
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= nodeNum; ++i) {
		int degree = rand() % (nodeNum - 1) + 1;
		list<int> temp;
		for (int j = 1; j <= nodeNum; ++j) {
			if (j == i) continue;
			if (graph.at(j).find(i) != graph.at(j).end()) {
				graph.at(i).insert(pair<int, int>(j, graph.at(j).find(i)->second));
				--degree;
				continue;
			}
			temp.insert(temp.end(), j);
		}
		for (int j = 1; j <= degree; ++j) {
			int ranNum = rand() % temp.size();
			list<int>::iterator li = temp.begin();
			for (int k = 0; k < ranNum; k++) ++li;
			int ranNum2 = rand() % 100 + 1;
			graph.at(i).insert(pair<int, int>(*li, ranNum2));
			graph.at(*li).insert(pair<int, int>(i, ranNum2));
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
	for (int i = 1; i < graph.size(); i++) {
		map<int, int>::iterator mi;
		cout << "Node " << i << "\t: ";
		for (mi = graph.at(i).begin(); mi != graph.at(i).end(); ++mi) {
			cout << mi->first << "(" << mi->second << ") ";
		}
		cout << endl;
	}
}

// Kruskal
void Kruskal::doAlgorithm() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	typedef struct { int vertex; int target; int cost; } HalfGraph;
	vector<HalfGraph> vh;
	for (int i = 1; i < graph.size(); i++)
		for (map<int, int>::iterator mi = graph.at(i).begin(); mi != graph.at(i).end(); mi++)
			if (mi->first > i) vh.push_back(HalfGraph{ i, mi->first, mi->second });
	sort(vh.begin(), vh.end(), [](HalfGraph first, HalfGraph second)->bool {return first.cost < second.cost ? true : false; });
	vector<HalfGraph>::iterator hgit = vh.begin();
	vector<set<int>> vertexes;
	for (int i = 0; i < graph.size() - 1; ++i) vertexes.push_back(set<int>{i + 1});
	while (vertexes.at(0).size() < graph.size() - 1) {
		int index = -1;
		for (int i = 0; i < vertexes.size(); ++i) 
			if (vertexes.at(i).find(hgit->vertex) != vertexes.at(i).end()) {index = i; break;}
		for (int i = 0; i < vertexes.size(); ++i) {
			if (vertexes.at(i).find(hgit->target) != vertexes.at(i).end()) {
				if (i == index) {
					hgit = vh.erase(hgit);
					break;
				}
				else if (i > index) {
					vertexes.at(index).insert(vertexes.at(i).begin(), vertexes.at(i).end());
					vertexes.at(i).clear();
				}
				else {
					vertexes.at(i).insert(vertexes.at(index).begin(), vertexes.at(index).end());
					vertexes.at(index).clear();
				}
				hgit++;
				break;
			}
		}
	}
	for (int i = 0; i < graph.size() - 2; i++) 
		cout << "vertex : " << vh.at(i).vertex << ", target : " << vh.at(i).target << ", cost : " << vh.at(i).cost << endl;
}

// Prim
void Prim::doAlgorithm() {
	if (graph.size() == 0) {
		cout << "Create a graph first." << endl;
		return;
	}
	set<int> sPrim; sPrim.insert(1);
	vector<int> target, cost; 
	cost.reserve(graph.size() - 2);	target.reserve(graph.size() - 2);
	for (int i = 0; i < graph.size() - 2; ++i) {
		int minCostNode = 1, min = INT_MAX;
		for (set<int>::iterator si = sPrim.begin(); si != sPrim.end(); si++) {
			for (map<int, int>::iterator mi = graph.at(*si).begin(); mi != graph.at(*si).end(); mi++) {
				if (sPrim.find(mi->first) == sPrim.end()) {
					if (min > mi->second) {
						min = mi->second;
						minCostNode = mi->first;
					}
				}
			}
		}
		sPrim.insert(minCostNode);
		target.push_back(minCostNode);
		cost.push_back(min);
	}
	cout << "Prim result : start node 1" << endl;
	for (int i = 0; i < cost.size(); ++i) 
		cout << "target : " << target.at(i) << ", cost : " << cost.at(i) << endl;
}