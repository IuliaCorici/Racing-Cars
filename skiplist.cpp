// Copyright 2019 Corici Iulia 314CA
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>

// struct to implement node in Skip list
template <typename T> struct Node {
 public:
    T data;
    int level;
    // array to hold pointers to node of different level
    Node<T> **next;
    Node(T data, int level) {
        this->data = data;
        this->level = level;
        // allocate memory to next
        next = new Node<T>* [level + 1];
        // and setting to NULL the array
        for (int i = 0; i < level + 1; i++) {
        next[i] = (Node<T>*) nullptr;
        }
    }
    ~Node() {
    	delete [] next;
    }
};
// class for Skip list
template <typename T> class SkipList {
 public:
    // pointer to head node
	Node<T> *head;
    // pointer to tail node
	Node<T> *tail;
    // maximum level for this skiplist
	int maximumLevel;
    // current level of skip list
	int currentLevel;
	SkipList(int maximumLevel, T data) {
		srand(time(0));
		this->maximumLevel = maximumLevel;
		currentLevel = maximumLevel - 1;
        T b = data * -1;
        // create head and tail nodes and initialize data
		head = new  Node<T>(data, maximumLevel);
		tail = new Node<T>(b, maximumLevel);
		for (int i = 0; i < maximumLevel; i++) {
			head->next[i] = tail;
		}
	}
    // destructor
	~SkipList() {
		Node<T>* aux;
		Node<T>* forward;
		aux = head;
		while (aux) {
			forward = aux->next[0];
			delete aux;
			aux = forward;
		}
	}
    // returns a random number smaller than maximum level
    int randomLevel() {
        return rand() % maximumLevel;
    }
    // insert given data in skip list
    bool insert(T data) {
        int lvl = 0;
        // create prev array to hold pointers to previous data of the
        // given one and initialize it
    	Node<T>** prev = new Node<T>* [maximumLevel + 1];
    	Node<T>* aux = head;
    	T aux_value;
        // search for data smaller than given data
    	for (int i = currentLevel; i >= 0; i--) {
    		aux_value = aux->next[i]->data;
    		while (aux->next[i] != nullptr && aux_value < data) {
    			aux = aux->next[i];
    			aux_value = aux->next[i]->data;
    		}
    		prev[i] = aux;
    	}
        // found position on level 0 to insert data
    	aux = aux->next[0];
    	aux_value = aux->data;
        // if there is already there return false
    	if (aux_value == data) {
    		delete [] prev;
    		return false;
    	} else {
            // insert data on random level
    		lvl = randomLevel();
    		if (lvl > currentLevel) {
    			for (int i = currentLevel + 1; i <= lvl; i++)
    				prev[i] = head;
                currentLevel = lvl;
    		}
    		Node<T>* node = new Node<T>(data, lvl);
    		for (int i = 0; i <= lvl; i++) {
    			node->next[i] = prev[i]->next[i];
    			prev[i]->next[i] = node;
    		}
    	}
    	delete [] prev;
        // insertion done successfully
    	return true;
    }
    // remove given data
    bool remove(T data) {
        // create prev array to hold pointers to previous data of the
        // given one and initialize it
    	Node<T>** prev = new Node<T>* [maximumLevel + 1];
    	Node<T>* aux = head;
    	T aux_value;
        // search for data smaller than given data
    	for (int i = currentLevel; i >= 0; i--) {
    		aux_value = aux->next[i]->data;
    		while (aux->next[i] != nullptr && aux_value < data) {
    			aux = aux->next[i];
    			aux_value = aux->next[i]->data;
    		}
    		prev[i] = aux;
    	}
        // found position on level 0 to remove given data
    	aux = aux->next[0];
    	aux_value = aux->data;
    	if (aux != nullptr && aux_value == data) {
            // if at level i, next node is not the one we need, break loop
    		for (int i = 0; i <= currentLevel; i++) {
    			if (prev[i]->next[i] != aux)
    				break;
    			prev[i]->next[i] = aux->next[i];
    		}
    		delete aux;
            // remove levels having no elements
    		while ((currentLevel > 0) &&
    		((head->next[currentLevel]->data == tail->data)))
    		currentLevel--;
	    	delete [] prev;
            // removal done successfully
    	    return true;
    	} else {
	    	delete [] prev;
    		return false;
    	}
    }
    // gets the k node in the skip list
    T get_value(int k) {
        Node<T> *node;
        int j = 0;
        // start at level 0
        node = head->next[0];
            while (node != tail) {
            // if it's the k-th node return its data
            if (j == k) {
                return node->data;
            }
            node = node->next[0];
            j++;
            }
        return T{};
    }
    // prints the list on levels
    void print_list() {
    	std::cout << "\n*****Skip List*****" << "\n";
        Node<T> *node;
		for (int i = 0; i <= currentLevel; i++) {
       		node = head->next[i];
        	std::cout << "Level " << i <<": \n";
        	while (node != tail) {
            std::cout << node->data;
            node = node->next[i];
            }
        std::cout << "\n";
        }
    }
};
class Pilot {
 public:
	int idx;  // index of the pilot
	int time;  // time they get in the race
	int prev;  // previous position in the scoreboard
	int points;  // score
	int prev_print;  // position at last command "print"
	Pilot() {
		time = 0;
	    idx = 0;
		prev = 0;
		points = 0;
		prev_print = 0;
	}
	// copy-constructor
	Pilot(const Pilot& other) {
		this->time = other.time;
		this->idx = other.idx;
		this->prev = other.prev;
		this->points = other.points;
		this->prev_print = other.prev_print;
	}
	// copy assignament
	Pilot& operator=(const Pilot& other) {
		this->time = other.time;
		this->idx = other.idx;
		this->prev = other.prev;
		this->points = other.points;
		this->prev_print = other.prev_print;
		return *this;
	}
	// destructor
	~Pilot() {}
	// overloading "*" for the index of the pilot
	Pilot operator*(const int& x) {
		this->idx = x * this->idx;
		return *this;
	}
	// overloading "<"  and "==" just to compare the index
	bool operator<(const Pilot& other) {
		return this->idx < other.idx;
	}
	bool operator==(const Pilot& other) {
		if (this->idx == other.idx) return true;
		return false;
	}
	friend std::ostream& operator<< (std::ostream &out, const Pilot& pilot);
};

std::ostream& operator<< (std::ostream &out, const Pilot& pilot) {
  	std::cout<< "Pilot " << pilot.idx + 1 << " has got " << pilot.points <<
  	" points in " << pilot.time << " seconds \n";
  	return out;
}
// compares the pilots by how fast they are in the race
// and if equal by their position in the scoreboard
bool compare_time(Pilot a, Pilot b) {
	if ( a.time == b.time )
		return a.prev < b.prev;
	return a.time < b.time;
}
// compares the pilots by the scores they have got so far
// and if equal by their index
bool compare_score(Pilot a, Pilot b) {
	if (a.points == b.points)
		return a.idx < b.idx;
	else
		return a.points > b.points;
}
// calculates the score of each pilot
void make_points(Pilot* v, const int in_race, int a, int n) {
	int number_of_points = in_race / 2;
	int j = a;
    while (j < n) {
	    while (number_of_points) {
            v[j].points += number_of_points;
            --number_of_points;
            j++;
        }
        // if there is an odd number of pilots then no one gets 0 points
        // so number_of_points = 0 is skipped
        if (in_race % 2 == 0) {
            --number_of_points;
        }
        while (number_of_points >= (-1) * (in_race / 2)) {
            v[j].points += number_of_points;
            --number_of_points;
            j++;
        }
    }
}
int main() {
	// n is number of pilots
	// m is number of races
	// k is number of commands "print"
	// in_race counts the number of pilots who took part in the race
	// last_positions is an array which holds the previous positions
	int n = 0, i = 0, j = 0, m = 0, k = 0, in_race = 0;
	std::string word;
	Pilot *v;
	// creating a pilot in order to initialize the skiplist
	Pilot initial;
    initial.idx = -510;
    initial.time = 6;
	int *last_positions;
	int number_of_prints = 0;
    // open the input and output files
	std::ifstream filein("races.in");
	std::ofstream fileout("races.out");
	// reading data from input file
	filein >> n >> m >> k;
	// creating a skiplist in order to hold the pilots based on index
	SkipList<Pilot>mylist((int)log(n), initial);
    v = new Pilot[n + 1];
    last_positions = new int[n + 1];
	for (i = 0; i < n; i++) {
		last_positions[i] = i;
		v[i].idx = i;
	}
	for (i = 0; i < m + k; i++) {
		filein  >> word;
		// if it's not "print" then read the times that pilots got in the race
		if (word != "print") {
			in_race = 0;
			std::stringstream file_virtual(word);
			// assigning data to the pilots
			file_virtual >> v[0].time;
			if (v[0].time != 0)
				in_race++;
			for (j = 1; j < n; j++) {
				filein >> v[j].time;
				if (v[j].time != 0)
					in_race++;
			}
			// updating their position in the previous race
            for (j = 0; j < n; j++)
				v[j].prev = last_positions[j];
			// sorting the pilots on how fast they are in the current race
			std::sort(v, v + n, compare_time);
			// skipping the number of pilots who got 0seconds
            int a = n - in_race;
            // calculating their scores
            make_points(v, in_race, a, n);
            // sorting the pilots on who has got most points
            std::sort(v, v + n, compare_score);
            // updating last_positions for next race
			for (j = 0; j < n; j++) {
				last_positions[v[j].idx] = j;
			}
	        // inserting the pilots in the skiplist
			for (j = 0; j < n; j++)
		        mylist.insert(v[j]);
            // getting the j pilot and assigning it to v[j] in the initial array
		    for (j = 0; j < n; j++)
		    	v[j] = mylist.get_value(j);
            // empty the skiplist
		    for (j = 0; j < n; j++)
		        mylist.remove(v[j]);
		} else {
			number_of_prints++;
			std::sort(v, v + n, compare_score);
			// if it's the first print
			if (number_of_prints == 1) {
			 	for (j = 0; j < n; j++){
			 	   fileout << v[j].idx + 1 << " " << v[j].points << " 0\n";
			 	}
                fileout << "\n";
			} else {
				for (j = 0; j < n; j++) {
			   		fileout << v[j].idx + 1 << " " << v[j].points << " " <<
			   		v[j].prev_print  - j << "\n";
				}
            	fileout << "\n";
		    }
		    // updating the position they have at this "print"
			for (j = 0; j < n; j++)
			  v[j].prev_print = j;
			// sorting the pilots again on index using skiplist
            for (j = 0; j < n; j++)
		        mylist.insert(v[j]);
		    for (j = 0; j < n; j++)
		     	v[j] = mylist.get_value(j);
		    for (j = 0; j < n; j++)
		        mylist.remove(v[j]);
	    }
    }
	delete [] v;
    delete [] last_positions;
    filein.close();
    fileout.close();
}

