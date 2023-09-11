#include "Point2D.cpp"
#include "Point3D.cpp"
#include "Line2D.cpp"
#include "Line3D.cpp"
#include <algorithm>
#include <typeinfo>
#include <iomanip>

using namespace std;

//needs for split function
char ch;
int choices;

//reading data
string data;

//hit enter to go back to main menu
string goBack;

//total records read
int total_records;

//variables to display and sort
string filter = "Point2D";
string sort_by = "x-ordinate";
string order = "ASC";

bool quit_sort;
string filter_option;

//point2d vectors
vector<string> pt2d_duplicate;
vector<Point2D> pt2d_vector;

//point3d vectors
vector<string> pt3d_comma_split;
vector<string> pt3d_duplicate;
vector<Point3D> pt3d_vector;

//line2d vectors
vector<Line2D> l2d_vector;
vector<string> l2d_duplicate;

//line3d vectors
vector<Line3D> l3d_vector;
vector<string> l3d_duplicate;
vector<string> l3d_comma_split_pt1;
vector<string> l3d_comma_split_pt2;

//sub-methods
void split_pt3d(string str, char separator);
void split_l3d_pt1(string str, char separator);
void split_l3d_pt2(string str, char separator);
void sortP2D();
void sortP3D();
void sortL2D();
void sortL3D();
bool check_int(string input);

//main methods
void readFile();
void writeFile();
void additionalFeature();

//checking if the input is interger or not
bool check_int(string input){
	for(int i = 0; i < input.length(); i++){
		if(isdigit(input[i]) == false){
			return false;
		}
	}
	return true;
}

//additional feature to put new points to records
void additionalFeature(){
	bool add_quit = false;
	while(!add_quit){
		string point;
		cout << "\n\t1) Point2D" << endl;
		cout << "\t2) Point3D" << endl;
		cout << "\nSelect point you want to add: ";
		cin >> point;
		
		if(point == "1"){
			bool error = true;
			string new_x;
			string new_y;
			while(error){
				cin.ignore();
				cout << "\nEnter x-ordinate: ";
				cin >> new_x;
				if(check_int(new_x) == false){
					cout << "Invalid input for x-ordinate. Try again." << endl;
					continue;
				}
				cin.ignore();
				cout << "Enter y-ordinate: ";
				cin >> new_y;
				if(check_int(new_y) == false){
					cout << "Invalid input for y-ordinate. Try again." << endl;
					continue;
				}
				Point2D pt2d(stoi(new_x), stoi(new_y));
				if(count(pt2d_duplicate.begin(), pt2d_duplicate.end(), new_x+","+new_y)){
					cout << "\nThis Point2D already exist." << endl;
					continue;
				}else{
					pt2d_duplicate.push_back(new_x+","+new_y);
					pt2d_vector.push_back(pt2d);
					cout << "\nThe point successfully added to the records." << endl;
					cout << "Going back to main menu...\n" << endl;
				}
				error = false;
			}
			
			add_quit = true;
		}
		else if(point == "2"){
			bool error = true;
			string new_x;
			string new_y;
			string new_z;
			while(error){
				cin.ignore();
				cout << "\nEnter x-ordinate: ";
				cin >> new_x;
				if(check_int(new_x) == false){
					cout << "Invalid input for x-ordinate. Try again." << endl;
					continue;
				}
				cin.ignore();
				cout << "Enter y-ordinate: ";
				cin >> new_y;
				if(check_int(new_y) == false){
					cout << "Invalid input for y-ordinate. Try again." << endl;
					continue;
				}
				cin.ignore();
				cout << "Enter z-ordinate: ";
				cin >> new_z;
				if(check_int(new_z) == false){
					cout << "Invalid input for z-ordinate. Try again." << endl;
					continue;
				}
				Point3D pt3d(stoi(new_x),stoi(new_y),stoi(new_z));
				if(count(pt3d_duplicate.begin(), pt3d_duplicate.end(), new_x+","+new_y+","+new_z)){
					cout << "\nThis Point3D already exist." << endl;
					continue;
				}
				else{
					pt3d_duplicate.push_back(new_x+","+new_y+","+new_z);
					pt3d_vector.push_back(pt3d);
					cout << "\nThe point successfully added to the records." << endl;
					cout << "Going back to main menu...\n" << endl;
				}
				error = false;
			}
			
			add_quit = true;
		}
		else{
			cout << "\nInvalid choice. Try again." << endl;
		}
	}
}

//writing records into the file
void writeFile(){
	string filename;
	ofstream writeFile;
	cout << "\nPlease enter filename: ";
	cin >> filename;
	
	writeFile.open(filename);
		if(writeFile.good()){
			if(filter == "Point2D"){
				
				writeFile << setw(5) << right << "X" << setw(5) << right << "Y" << "    " << left << "Dist. Fr Origin" << endl;
				writeFile << "------------------------------" << endl;
				for(int i = 0; i < pt2d_vector.size(); i++){
					cout << "[" << setw(4) << right << pt2d_vector[i].getX() << "," << setw(4) << pt2d_vector[i].getY() << "]" << "   " << left << setprecision(3) << fixed << pt2d_vector[i].getScalarValue() << endl;
				}
			}
			else if(filter == "Point3D"){
				
				writeFile << setw(5) << right << "X" << setw(5) << right << "Y" << setw(5) << right << "Z" << "    " << left << "Dist. Fr Origin" << endl;
				writeFile << "-----------------------------------" << endl;
					for(int i = 0; i < pt3d_vector.size(); i++){
						writeFile << "[" << setw(4) << right << pt3d_vector[i].getX() << "," << setw(4) << right << pt3d_vector[i].getY() << "," << setw(4) << right << pt3d_vector[i].getZ() << "]" << "   " << left << setprecision(3) << fixed << pt3d_vector[i].getScalarValue() << endl;
					}
			}
			else if(filter == "Line2D"){
				
				writeFile << setw(5) << right << "P1-X" << setw(5) << right << "P1-Y" << "    " << setw(5) << right << "P2-X" << setw(5) << right << "P2-Y" << "    " << left << "Length" << endl;
				writeFile << "------------------------------------" << endl;
				for(int i = 0; i < l2d_vector.size(); i++){
					writeFile << "[" << setw(4) << right << l2d_vector[i].getPt1().getX() << "," << setw(4) << right << l2d_vector[i].getPt1().getY() << "]" << setw(4) << "[" << setw(4) << right << l2d_vector[i].getPt2().getX() << "," << setw(4) << right << l2d_vector[i].getPt2().getY() << "]" << "   " << left << setprecision(3) << fixed << l2d_vector[i].getScalarValue() << endl;
				}
			}
			else if(filter == "Line3D"){
				
				writeFile << setw(5) << right << "P1-X" << setw(5) << right << "P1-Y" << setw(5) << right << "P1-Z" << "    " << setw(5) << right << "P2-X" << setw(5) << right << "P2-Y" << setw(5) << right << "P2-Z" << "    " << left << "Length" << endl;
				writeFile << "----------------------------------------------" << endl;
				for(int i = 0; i < l3d_vector.size(); i++){
					writeFile << "[" << setw(4) << right << l3d_vector[i].getPt1().getX() << "," << setw(4) << right << l3d_vector[i].getPt1().getY() << "," << setw(4) << right << l3d_vector[i].getPt1().getZ() << "]" << setw(4) << "[" << setw(4) << right << l3d_vector[i].getPt2().getX() << "," << setw(4) << right << l3d_vector[i].getPt2().getY() << "," << setw(4) << right << l3d_vector[i].getPt2().getZ() << "]" << "   " << left << setprecision(3) << fixed << l3d_vector[i].getScalarValue() << endl;
				}
			}
	}
	else{
		cout << "Invalid file. Try again" << endl;
	}
	writeFile.close();
}

//reading records from txt file
void readFile(){
	string filename;
	ifstream file;
	
	cout << "Please enter filename: ";
	cin >> filename;

	file.open(filename);
	if(file.good()){
		while(!file.eof()){
			getline(file, data);
			
			pt3d_comma_split.clear();
			l3d_comma_split_pt1.clear();
			l3d_comma_split_pt2.clear();
			
			if(data.find("Point2D") != string::npos){
				size_t finder_start = data.find("[");
				size_t finder_end = data.find("]");
				string temp;
				temp.append(data, finder_start+1, finder_end-finder_start-1);
				temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
				int sign = temp.find(",");
				string x_str = temp.substr(0, sign);
				string y_str = temp.substr(sign + 1);
				int x = stoi(x_str);
				int y = stoi(y_str);
				
				Point2D pt2d(x,y);
				if(count(pt2d_duplicate.begin(), pt2d_duplicate.end(), temp)){
					continue;
				}else{
					pt2d_duplicate.push_back(temp);
					pt2d_vector.push_back(pt2d);
				}
			}
			
			else if(data.find("Point3D") != string::npos){
				
				size_t finder_start = data.find("[");
				size_t finder_end = data.find("]");
				string temp;
				temp.append(data, finder_start+1, finder_end-finder_start-1);
				temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
				split_pt3d(temp, ',');
				
				int x = stoi(pt3d_comma_split[0]);
				int y = stoi(pt3d_comma_split[1]);
				int z = stoi(pt3d_comma_split[2]);
				
				Point3D pt3d(x,y,z);
				if(count(pt3d_duplicate.begin(), pt3d_duplicate.end(), temp)){
					continue;
				}
				else{
					pt3d_duplicate.push_back(temp);
					pt3d_vector.push_back(pt3d);
				}
			}
			else if(data.find("Line2D") != string::npos){
				size_t finder_start_pt1 = data.find("[");
				size_t finder_end_pt1 = data.find("]");
				
				size_t finder_start_pt2 = data.find("[", finder_start_pt1+1);
				size_t finder_end_pt2 = data.find("]", finder_end_pt1+1);
				
				string pt1_str;
				pt1_str.append(data, finder_start_pt1+1, finder_end_pt1-finder_start_pt1-1);
				pt1_str.erase(remove(pt1_str.begin(), pt1_str.end(), ' '), pt1_str.end());
				string pt2_str;
				pt2_str.append(data, finder_start_pt2+1, finder_end_pt2-finder_start_pt2-1);
				pt2_str.erase(remove(pt2_str.begin(), pt2_str.end(), ' '), pt2_str.end());
				int sign = pt1_str.find(",");
				string x_pt1 = pt1_str.substr(0, sign);
				string y_pt1 = pt1_str.substr(sign+1);
				
				int pt1_x = stoi(x_pt1);
				int pt1_y = stoi(y_pt1);
				
				Point2D pt1(pt1_x, pt1_y);
				
				int sign1 = pt2_str.find(",");
				string x_pt2 = pt2_str.substr(0, sign1);
				string y_pt2 = pt2_str.substr(sign1+1);
				
				int pt2_x = stoi(x_pt2);
				int pt2_y = stoi(y_pt2);
				
				Point2D pt2(pt2_x, pt2_y);
				
				Line2D l2d(pt1, pt2);
				if(count(l2d_duplicate.begin(), l2d_duplicate.end(), "pt1:"+pt1_str+"pt2:"+pt2_str) or count(l2d_duplicate.begin(), l2d_duplicate.end(), "pt1:"+pt2_str+"pt2:"+pt1_str)){
					continue;
				}
				else{
					l2d_duplicate.push_back("pt1:"+pt1_str+"pt2:"+pt2_str);
					l2d_vector.push_back(l2d);
				}
				
			}
			else if(data.find("Line3D") != string::npos){
				size_t finder_start_pt1 = data.find("[");
				size_t finder_end_pt1 = data.find("]");
				
				size_t finder_start_pt2 = data.find("[", finder_start_pt1+1);
				size_t finder_end_pt2 = data.find("]", finder_end_pt1+1);
				
				string pt1_str;
				pt1_str.append(data, finder_start_pt1+1, finder_end_pt1-finder_start_pt1-1);
				pt1_str.erase(remove(pt1_str.begin(), pt1_str.end(), ' '), pt1_str.end());
				string pt2_str;
				pt2_str.append(data, finder_start_pt2+1, finder_end_pt2-finder_start_pt2-1);
				pt2_str.erase(remove(pt2_str.begin(), pt2_str.end(), ' '), pt2_str.end());
				split_l3d_pt1(pt1_str, ',');
				split_l3d_pt2(pt2_str, ',');
				
				int pt1_x = stoi(l3d_comma_split_pt1[0]);
				int pt1_y = stoi(l3d_comma_split_pt1[1]);
				int pt1_z = stoi(l3d_comma_split_pt1[2]);
				
				int pt2_x = stoi(l3d_comma_split_pt2[0]);
				int pt2_y = stoi(l3d_comma_split_pt2[1]);
				int pt2_z = stoi(l3d_comma_split_pt2[2]);
				
				Point3D p3d_pt1(pt1_x, pt1_y, pt1_z);
				Point3D p3d_pt2(pt2_x, pt2_y, pt2_z);
				
				Line3D l3d(p3d_pt1, p3d_pt2);
				if(count(l3d_duplicate.begin(), l3d_duplicate.end(), "pt1:"+pt1_str+"pt2:"+pt2_str) or count(l3d_duplicate.begin(), l3d_duplicate.end(), "pt1:"+pt2_str+"pt2:"+pt1_str)){
					continue;
				}
				else{
					l3d_duplicate.push_back("pt1:"+pt1_str+"pt2:"+pt2_str);
					l3d_vector.push_back(l3d);
				}
				
			}
			
			
		}
		
	}
	else{
		cout << "Invalid filename" << endl;
	}
	file.close();
}

int main()
{
	bool quit = false;
	while (!quit){
		bool name_error = false;
		bool warp_error = false;
		cout << endl;
		cout << "Student ID\t: 8039173" << endl;
		cout << "Student Name\t: Min Khant Thu" << endl;
		cout << "-----------------------------------------------" << endl;
		
		cout << "Welcome to Assn3 program!" << endl;
		cout << endl;
	
		int n = 1;
		
		//put all the options in array
		string options[] = {"Read in data", "Specify filtering criteria (current: "+ filter +")", "Specify sorting criteria (current: " + sort_by + ")", "Specify sorting order (current: "+ order +")", "View data", "Store data","Quit","Add new points to the records"};
	
		for(string option: options){
			cout << n << ")\t" << option << endl;
			n++;
		}
		
		//asking user what option he wants to choose
		cout << "\nPlease enter your choice: ";
		
		if(cin >> choices)switch(choices){
			case 1:
				cout << endl;
				readFile();
				total_records = pt2d_vector.size()+pt3d_vector.size()+l2d_vector.size()+l3d_vector.size();
				cout << "\n" << total_records << " records read in successfully!\n" << endl;
				cout << "Going back to main menu ...\n" << endl;
				break;
				
			case 2:
				quit_sort = false;
				while(!quit_sort){
					cout << "\n[ Specifying filtering criteria (current: "+ filter +") ]\n" << endl;
					cout << "\ta)\tPoint2D records" << endl;
					cout << "\tb)\tPoint3D records" << endl;
					cout << "\tc)\tLine2D records" << endl;
					cout << "\td)\tLine3D records" << endl;
					
					cout << "\nPlease enter your criteria (a-d): ";
					cin >> filter_option;
					if(filter_option == "a"){
						filter = "Point2D";
						if(sort_by == "Pt. 1" or sort_by == "Pt. 2" or sort_by == "z-ordinate"){
							sort_by = "x-ordinate";
						}
						quit_sort = true;
					}
					else if(filter_option == "b"){
						filter = "Point3D";
						if(sort_by == "Pt. 1" or sort_by == "Pt. 2"){
							sort_by = "x-ordinate";
						}
						quit_sort = true;
					}
					else if(filter_option == "c"){
						filter = "Line2D";
						if(sort_by == "x-ordinate" or sort_by == "y-ordinate"){
							sort_by = "Pt. 1";
						}
						quit_sort = true;
					}
					else if(filter_option == "d"){
						filter = "Line3D";
						if(sort_by == "x-ordinate" or sort_by == "y-ordinate"){
							sort_by = "Pt. 1";
						}
						quit_sort = true;
					}
					else{
						cout << "Choose the options given." << endl;
					}
				}
				cout << "Filter criteria successfully set to '" << filter << "'!\n" << endl;
				break;
			case 3:
				quit_sort = false;
				while(!quit_sort){
					cout << "\n[ Specifying sorting criteria (current: "+ sort_by +") ]\n" << endl;
					if(filter == "Point2D"){
						cout << "\ta)\tx-ordinate value" << endl;
						cout << "\tb)\ty-ordinate value" << endl;
						cout << "\tc)\tLength value" << endl;
						
						cout << "\nPlease enter your criteria (a-c): ";
						cin >> filter_option;
						if(filter_option == "a"){
							sort_by = "x-ordinate";
							quit_sort = true;
						}
						else if(filter_option == "b"){
							sort_by = "y-ordinate";
							quit_sort = true;
						}
						else if(filter_option == "c"){
							sort_by = "Length";
							quit_sort = true;
						}
						else{
							cout << "Choose the options given." << endl;
						}
					}
					else if(filter == "Point3D"){
						cout << "\ta)\tx-ordinate value" << endl;
						cout << "\tb)\ty-ordinate value" << endl;
						cout << "\tc)\tz-ordinate value" << endl;
						cout << "\td)\tLength value" << endl;
						cout << "\nPlease enter your criteria (a-d): ";
						cin >> filter_option;
						if(filter_option == "a"){
							sort_by = "x-ordinate";
							quit_sort = true;
						}
						else if(filter_option == "b"){
							sort_by = "y-ordinate";
							quit_sort = true;
						}
						else if(filter_option == "c"){
							sort_by = "z-ordinate";
							quit_sort = true;
						}
						else if(filter_option == "d"){
							sort_by = "Length";
							quit_sort = true;
						}
						else{
							cout << "Choose the options given." << endl;
						}
					}
					else if(filter == "Line2D" or filter == "Line3D"){
						cout << "\ta)\tPt. 1's(x,y) values" << endl;
						cout << "\tb)\tPt. 2's(x,y) values" << endl;
						cout << "\tc)\tLength value" << endl;
						cout << "\nPlease enter your criteria (a-c): ";
						cin >> filter_option;
						if(filter_option == "a"){
							sort_by = "Pt. 1";
							quit_sort = true;
						}
						else if(filter_option == "b"){
							sort_by = "Pt. 2";
							quit_sort = true;
						}
						else if(filter_option == "c"){
							sort_by = "Length";
							quit_sort = true;
						}
						else{
							cout << "Choose the options given." << endl;
						}
					}
				
				}
				cout << "Sorting criteria successfully set to '" << sort_by << "'!\n" << endl;
				break;
			case 4:
				quit_sort = false;
				while(!quit_sort){
					cout << "\n[ Specifying sorting order (current: "+ order +") ]\n" << endl;
					cout << "\ta)\tASC (Ascending order)" << endl;
					cout << "\tb)\tDSC (Descending order)" << endl;
					
					cout << "\nPlease enter your criteria (a-b): ";
					cin >> filter_option;
					if(filter_option == "a"){
						order = "ASC";
						quit_sort = true;
					}
					else if(filter_option == "b"){
						order = "DSC";
						quit_sort = true;
					}
					else{
						cout << "Choose the options given." << endl;
					}
				}
				cout << "Sorting order successfully set to '" << order << "'!\n" << endl;
				break;
			case 5:
				cout << endl;
				cin.ignore();
				cout << "[View data...]" << endl;
				cout << "filtering criteria: " << filter << endl;
				cout << "sorting criteria: " << sort_by << endl;
				cout << "sorting order: " << order << endl;
				cout << endl;
				if(filter == "Point2D"){
					sortP2D();
					cout << setw(5) << right << "X" << setw(5) << right << "Y" << "    " << left << "Dist. Fr Origin" << endl;
					cout << "------------------------------" << endl;
					for(int i = 0; i < pt2d_vector.size(); i++){
						cout << "[" << setw(4) << right << pt2d_vector[i].getX() << "," << setw(4) << pt2d_vector[i].getY() << "]" << "   " << left << setprecision(3) << fixed << pt2d_vector[i].getScalarValue() << endl;
					}
				}
				else if(filter == "Point3D"){
					sortP3D();
					cout << setw(5) << right << "X" << setw(5) << right << "Y" << setw(5) << right << "Z" << "    " << left << "Dist. Fr Origin" << endl;
					cout << "-----------------------------------" << endl;
						for(int i = 0; i < pt3d_vector.size(); i++){
							cout << "[" << setw(4) << right << pt3d_vector[i].getX() << "," << setw(4) << right << pt3d_vector[i].getY() << "," << setw(4) << right << pt3d_vector[i].getZ() << "]" << "   " << left << setprecision(3) << fixed << pt3d_vector[i].getScalarValue() << endl;
						}
				}
				else if(filter == "Line2D"){
					sortL2D();
					cout << setw(5) << right << "P1-X" << setw(5) << right << "P1-Y" << "    " << setw(5) << right << "P2-X" << setw(5) << right << "P2-Y" << "    " << left << "Length" << endl;
					cout << "------------------------------------" << endl;
					for(int i = 0; i < l2d_vector.size(); i++){
						cout << "[" << setw(4) << right << l2d_vector[i].getPt1().getX() << "," << setw(4) << right << l2d_vector[i].getPt1().getY() << "]" << setw(4) << "[" << setw(4) << right << l2d_vector[i].getPt2().getX() << "," << setw(4) << right << l2d_vector[i].getPt2().getY() << "]" << "   " << left << setprecision(3) << fixed << l2d_vector[i].getScalarValue() << endl;
					}
				}
				else if(filter == "Line3D"){
					sortL3D();
					cout << setw(5) << right << "P1-X" << setw(5) << right << "P1-Y" << setw(5) << right << "P1-Z" << "    " << setw(5) << right << "P2-X" << setw(5) << right << "P2-Y" << setw(5) << right << "P2-Z" << "    " << left << "Length" << endl;
					cout << "----------------------------------------------" << endl;
					for(int i = 0; i < l3d_vector.size(); i++){
						cout << "[" << setw(4) << right << l3d_vector[i].getPt1().getX() << "," << setw(4) << right << l3d_vector[i].getPt1().getY() << "," << setw(4) << right << l3d_vector[i].getPt1().getZ() << "]" << setw(4) << "[" << setw(4) << right << l3d_vector[i].getPt2().getX() << "," << setw(4) << right << l3d_vector[i].getPt2().getY() << "," << setw(4) << right << l3d_vector[i].getPt2().getZ() << "]" << "   " << left << setprecision(3) << fixed << l3d_vector[i].getScalarValue() << endl;
					}
				}
				cout << endl;
				cout << "Please <enter> to go back to main menu...";
				getline(cin,goBack);
				
				
				break;
			case 6:
				writeFile();
				cout << "\n" << total_records << " records output successfully!\n" << endl;
				cout << "Going back to main menu ...\n" << endl;
				break;
			case 7:
				cout << endl;
				cout << "Program terminated..." << endl;
				quit = true;
				break;
			case 8:
				cout << endl;
				cout << "[Add new points to the records]" << endl;
				cout << endl;
				additionalFeature();
				break;
			default:
				cout << "\nInvalid choice. Try again." << endl;
				break;
		}
		else{
			cout << "\nInvalid input. Try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	return 0;
}

//splitting the string
void split_pt3d(string str, char seperator){
	int startIndex = 0, endIndex = 0;
	//splitting the string to chars
	for(int i = 0; i <= str.size(); i++){
		//if the char is equal to seperator or is the end of the string
		if(str[i] == seperator || i == str.size()){
			//make endIndex the index where we find the seperator
			endIndex = i;
			string temp;
			//adding all the previous chars excluding the seperator into a string
			temp.append(str, startIndex, endIndex - startIndex);
			//adding the string to a vector to use it later
			pt3d_comma_split.push_back(temp);
			//change the start for the next string to the index after the seperator or where we ended
			startIndex = endIndex + 1;
		}
	}
}
//splitting the string
void split_l3d_pt1(string str, char seperator){
	int startIndex = 0, endIndex = 0;
	//splitting the string to chars
	for(int i = 0; i <= str.size(); i++){
		//if the char is equal to seperator or is the end of the string
		if(str[i] == seperator || i == str.size()){
			//make endIndex the index where we find the seperator
			endIndex = i;
			string temp;
			//adding all the previous chars excluding the seperator into a string
			temp.append(str, startIndex, endIndex - startIndex);
			//adding the string to a vector to use it later
			l3d_comma_split_pt1.push_back(temp);
			//change the start for the next string to the index after the seperator or where we ended
			startIndex = endIndex + 1;
		}
	}
}
//splitting the string
void split_l3d_pt2(string str, char seperator){
	int startIndex = 0, endIndex = 0;
	//splitting the string to chars
	for(int i = 0; i <= str.size(); i++){
		//if the char is equal to seperator or is the end of the string
		if(str[i] == seperator || i == str.size()){
			//make endIndex the index where we find the seperator
			endIndex = i;
			string temp;
			//adding all the previous chars excluding the seperator into a string
			temp.append(str, startIndex, endIndex - startIndex);
			//adding the string to a vector to use it later
			l3d_comma_split_pt2.push_back(temp);
			//change the start for the next string to the index after the seperator or where we ended
			startIndex = endIndex + 1;
		}
	}
}
void sortP2D(){
	bool swap = true;
	while(swap){
		swap = false;
		if(sort_by == "x-ordinate" and order == "ASC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
				int x1 = pt2d_vector[i-1].getX();
				int x2 = pt2d_vector[i].getX();
				int y1 = pt2d_vector[i-1].getY();
				int y2 = pt2d_vector[i].getY();
				Point2D p1 = pt2d_vector[i-1];
				Point2D p2 = pt2d_vector[i];
				if(x1 > x2){
					pt2d_vector[i] = p1;
					pt2d_vector[i-1] = p2;
					swap = true;
				}
				else if(x1 == x2){
					if(y1 > y2){
						pt2d_vector[i] = p1;
						pt2d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
		}
		else if(sort_by == "x-ordinate" and order == "DSC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
				int x1 = pt2d_vector[i-1].getX();
				int x2 = pt2d_vector[i].getX();
				int y1 = pt2d_vector[i-1].getY();
				int y2 = pt2d_vector[i].getY();
				Point2D p1 = pt2d_vector[i-1];
				Point2D p2 = pt2d_vector[i];
				if(x1 < x2){
					pt2d_vector[i] = p1;
					pt2d_vector[i-1] = p2;
					swap = true;
				}
				else if(x1 == x2){
					if(y1 < y2){
						pt2d_vector[i] = p1;
						pt2d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
		}
		else if(sort_by == "y-ordinate" and order == "ASC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
				int x1 = pt2d_vector[i-1].getX();
				int x2 = pt2d_vector[i].getX();
				int y1 = pt2d_vector[i-1].getY();
				int y2 = pt2d_vector[i].getY();
				Point2D p1 = pt2d_vector[i-1];
				Point2D p2 = pt2d_vector[i];
				if(y1 > y2){
					pt2d_vector[i] = p1;
					pt2d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(x1 > x2){
						pt2d_vector[i] = p1;
						pt2d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
		}
		else if(sort_by == "y-ordinate" and order == "DSC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
				int x1 = pt2d_vector[i-1].getX();
				int x2 = pt2d_vector[i].getX();
				int y1 = pt2d_vector[i-1].getY();
				int y2 = pt2d_vector[i].getY();
				Point2D p1 = pt2d_vector[i-1];
				Point2D p2 = pt2d_vector[i];
				if(y1 < y2){
					pt2d_vector[i] = p1;
					pt2d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(x1 < x2){
						pt2d_vector[i] = p1;
						pt2d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
		}
		else if(sort_by == "Length" and order == "ASC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
			int l1 = pt2d_vector[i-1].getScalarValue();
			int l2 = pt2d_vector[i].getScalarValue();
			Point2D p1 = pt2d_vector[i-1];
			Point2D p2 = pt2d_vector[i];
			if(l1 > l2){
				pt2d_vector[i] = p1;
				pt2d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		else if(sort_by == "Length" and order == "DSC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
			int l1 = pt2d_vector[i-1].getScalarValue();
			int l2 = pt2d_vector[i].getScalarValue();
			Point2D p1 = pt2d_vector[i-1];
			Point2D p2 = pt2d_vector[i];
			if(l1 < l2){
				pt2d_vector[i] = p1;
				pt2d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		
	}
}
void sortP3D(){
	bool swap = true;
	while(swap){
		swap = false;
		if(sort_by == "x-ordinate" and order == "ASC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(x1 > x2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(x1 == x2){
					if(y1 > y2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(y1 == y2){
						if(z1 > z2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "x-ordinate" and order == "DSC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(x1 < x2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(x1 == x2){
					if(y1 < y2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(y1 == y2){
						if(z1 < z2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "y-ordinate" and order == "ASC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(y1 > y2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(x1 > x2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(x1 == x2){
						if(z1 > z2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "y-ordinate" and order == "DSC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(y1 < y2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(x1 < x2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(x1 == x2){
						if(z1 < z2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "z-ordinate" and order == "ASC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(z1 > z2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(z1 == z2){
					if(x1 > x2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(x1 == x2){
						if(y1 > y2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "z-ordinate" and order == "DSC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
				int x1 = pt3d_vector[i-1].getX();
				int x2 = pt3d_vector[i].getX();
				int y1 = pt3d_vector[i-1].getY();
				int y2 = pt3d_vector[i].getY();
				int z1 = pt3d_vector[i-1].getZ();
				int z2 = pt3d_vector[i].getZ();
				Point3D p1 = pt3d_vector[i-1];
				Point3D p2 = pt3d_vector[i];
				if(z1 < z2){
					pt3d_vector[i] = p1;
					pt3d_vector[i-1] = p2;
					swap = true;
				}
				else if(z1 == z2){
					if(x1 < x2){
						pt3d_vector[i] = p1;
						pt3d_vector[i-1] = p2;
						swap = true;
					}
					else if(x1 == x2){
						if(y1 < y2){
							pt3d_vector[i] = p1;
							pt3d_vector[i-1] = p2;
							swap = true;
						}
					}
				}
			}
		}
		else if(sort_by == "Length" and order == "ASC"){
			for(int i = 1; i < pt2d_vector.size(); i++){
			int l1 = pt3d_vector[i-1].getScalarValue();
			int l2 = pt3d_vector[i].getScalarValue();
			Point3D p1 = pt3d_vector[i-1];
			Point3D p2 = pt3d_vector[i];
			if(l1 > l2){
				pt3d_vector[i] = p1;
				pt3d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		else if(sort_by == "Length" and order == "DSC"){
			for(int i = 1; i < pt3d_vector.size(); i++){
			int l1 = pt3d_vector[i-1].getScalarValue();
			int l2 = pt3d_vector[i].getScalarValue();
			Point3D p1 = pt3d_vector[i-1];
			Point3D p2 = pt3d_vector[i];
			if(l1 < l2){
				pt3d_vector[i] = p1;
				pt3d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		
	}
}
void sortL2D(){
	bool swap = true;
	while(swap){
		swap = false;
		if(sort_by == "Pt. 1" and order == "ASC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int x1 = l2d_vector[i-1].getPt1().getX();
			int x2 = l2d_vector[i].getPt1().getX();
			int y1 = l2d_vector[i-1].getPt1().getY();
			int y2 = l2d_vector[i].getPt1().getY();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(x1 > x2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 > y2){
					l2d_vector[i] = p1;
					l2d_vector[i-1] = p2;
					swap = true;
				}
			}
			}
		}
		else if(sort_by == "Pt. 1" and order == "DSC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int x1 = l2d_vector[i-1].getPt1().getX();
			int x2 = l2d_vector[i].getPt1().getX();
			int y1 = l2d_vector[i-1].getPt1().getY();
			int y2 = l2d_vector[i].getPt1().getY();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(x1 < x2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 < y2){
					l2d_vector[i] = p1;
					l2d_vector[i-1] = p2;
					swap = true;
				}
			}
			}
		}
		else if(sort_by == "Pt. 2" and order == "ASC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int x1 = l2d_vector[i-1].getPt2().getX();
			int x2 = l2d_vector[i].getPt2().getX();
			int y1 = l2d_vector[i-1].getPt2().getY();
			int y2 = l2d_vector[i].getPt2().getY();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(x1 > x2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 > y2){
					l2d_vector[i] = p1;
					l2d_vector[i-1] = p2;
					swap = true;
				}
			}
			}
		}
		else if(sort_by == "Pt. 2" and order == "DSC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int x1 = l2d_vector[i-1].getPt2().getX();
			int x2 = l2d_vector[i].getPt2().getX();
			int y1 = l2d_vector[i-1].getPt2().getY();
			int y2 = l2d_vector[i].getPt2().getY();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(x1 < x2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 < y2){
					l2d_vector[i] = p1;
					l2d_vector[i-1] = p2;
					swap = true;
				}
			}
			}
		}
		else if(sort_by == "Length" and order == "ASC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int l1 = l2d_vector[i-1].getScalarValue();
			int l2 = l2d_vector[i].getScalarValue();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(l1 > l2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		else if(sort_by == "Length" and order == "DSC"){
			for(int i = 1; i < l2d_vector.size(); i++){
			int l1 = l2d_vector[i-1].getScalarValue();
			int l2 = l2d_vector[i].getScalarValue();
			Line2D p1 = l2d_vector[i-1];
			Line2D p2 = l2d_vector[i];
			if(l1 < l2){
				l2d_vector[i] = p1;
				l2d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		
	}
}
void sortL3D(){
	bool swap = true;
	while(swap){
		swap = false;
		if(sort_by == "Pt. 1" and order == "ASC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int x1 = l3d_vector[i-1].getPt1().getX();
			int x2 = l3d_vector[i].getPt1().getX();
			int y1 = l3d_vector[i-1].getPt1().getY();
			int y2 = l3d_vector[i].getPt1().getY();
			int z1 = l3d_vector[i-1].getPt1().getZ();
			int z2 = l3d_vector[i].getPt1().getZ();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(x1 > x2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 > y2){
					l3d_vector[i] = p1;
					l3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(z1 > z2){
						l3d_vector[i] = p1;
						l3d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
			}
		}
		else if(sort_by == "Pt. 1" and order == "DSC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int x1 = l3d_vector[i-1].getPt1().getX();
			int x2 = l3d_vector[i].getPt1().getX();
			int y1 = l3d_vector[i-1].getPt1().getY();
			int y2 = l3d_vector[i].getPt1().getY();
			int z1 = l3d_vector[i-1].getPt1().getZ();
			int z2 = l3d_vector[i].getPt1().getZ();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(x1 < x2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 < y2){
					l3d_vector[i] = p1;
					l3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(z1 < z2){
						l3d_vector[i] = p1;
						l3d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
			}
		}
		else if(sort_by == "Pt. 2" and order == "ASC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int x1 = l3d_vector[i-1].getPt2().getX();
			int x2 = l3d_vector[i].getPt2().getX();
			int y1 = l3d_vector[i-1].getPt2().getY();
			int y2 = l3d_vector[i].getPt2().getY();
			int z1 = l3d_vector[i-1].getPt1().getZ();
			int z2 = l3d_vector[i].getPt1().getZ();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(x1 > x2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 > y2){
					l3d_vector[i] = p1;
					l3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(z1 > z2){
						l3d_vector[i] = p1;
						l3d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
			}
		}
		else if(sort_by == "Pt. 2" and order == "DSC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int x1 = l3d_vector[i-1].getPt2().getX();
			int x2 = l3d_vector[i].getPt2().getX();
			int y1 = l3d_vector[i-1].getPt2().getY();
			int y2 = l3d_vector[i].getPt2().getY();
			int z1 = l3d_vector[i-1].getPt1().getZ();
			int z2 = l3d_vector[i].getPt1().getZ();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(x1 < x2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}else if(x1 == x2){
				if(y1 < y2){
					l3d_vector[i] = p1;
					l3d_vector[i-1] = p2;
					swap = true;
				}
				else if(y1 == y2){
					if(z1 < z2){
						l3d_vector[i] = p1;
						l3d_vector[i-1] = p2;
						swap = true;
					}
				}
			}
			}
		}
		else if(sort_by == "Length" and order == "ASC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int l1 = l3d_vector[i-1].getScalarValue();
			int l2 = l3d_vector[i].getScalarValue();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(l1 > l2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		else if(sort_by == "Length" and order == "DSC"){
			for(int i = 1; i < l3d_vector.size(); i++){
			int l1 = l3d_vector[i-1].getScalarValue();
			int l2 = l3d_vector[i].getScalarValue();
			Line3D p1 = l3d_vector[i-1];
			Line3D p2 = l3d_vector[i];
			if(l1 < l2){
				l3d_vector[i] = p1;
				l3d_vector[i-1] = p2;
				swap = true;
			}
			}
		}
		
	}
}
