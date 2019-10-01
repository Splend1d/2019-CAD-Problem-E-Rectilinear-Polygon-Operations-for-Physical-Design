#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <list>
#include <typeinfo>
#include <boost/polygon/polygon.hpp>
#include <cassert>
namespace gtl = boost::polygon;
using namespace boost::polygon::operators;
using namespace std;

typedef gtl::polygon_90_with_holes_data<long long> Polygon;
typedef gtl::rectangle_data<long long> Rectangle;
typedef gtl::polygon_90_data<long long> PolygonNoHoles;
typedef gtl::polygon_traits<Polygon>::point_type Point;
typedef std::vector<Polygon> Polygon_Set;
typedef std::vector<vector<Polygon> > Polygon_Master_Set;

std::vector< gtl::rectangle_data<long long> > rects;



int main(int argc,char *argv[])
{	
	// opening file
	ifstream myfile;//input_file
	const char* filename =argv[1];
	myfile.open(filename);
	if (!myfile) {
	    cerr << "Cannot open file \"" << filename << "\"!" << endl;
	    return false; }
	
	cout << "opening file from " << filename<<endl;
	
	string declare_start;
	myfile >> declare_start; // declare_start == "OPERATION"
	//cout << declare_start<<endl; 
	
	string operation_temp = "NULL";
	string last_operation;
	list<string> operation_list; // stores list of operations
	
	while(true){
		myfile >> operation_temp; // operation_temp == "M1" or "C1" or "SH"......
		if (operation_temp[0] == ';'){
			break;
		}
		//cout << operation_temp <<endl;
		operation_list.push_back(operation_temp);
	}
	last_operation = operation_list.back();
	operation_list.pop_back();
	cout << operation_list.size() << " operations" << endl;
	list<string>::iterator operation_it; // operation iterator: merge clip split
	Polygon polygon;
	Polygon_Set main_set;
	std::vector<Point> polygon_temp;
	int operation_read = 0;
	int poly_step_n = 0;
	Polygon_Master_Set queue_merge;
	Polygon_Master_Set queue_clip;
	//cout << 'o' << operation_list.size() << endl;
	for (operation_it = operation_list.begin();operation_it != operation_list.end();++operation_it){
		operation_read ++;
		//cout << "iter" << endl;
		Polygon_Set operation_set;
		gtl::clear(operation_set);
		string this_operation = "NA";
		while(true){
			myfile >> operation_temp;		
			if (operation_temp[0] == ';'){
				break;
			}
			this_operation = operation_temp;
			//cout << dump << endl;
			// read file until the polygon coordinates
		}
		string dump = "dump";
		myfile >> dump;
		
		
		string end_detector = "0";
		
		long long x_temp;
		long long y_temp;	
		while(true){ // each iteration manages an operation, as each iteration reads a polygon
			//gtl::clear(polygon);
			polygon_temp.clear();
			while(true){ // this while loop reads a polygon, as each iteration reads a node(x,y)
				
				myfile >> end_detector;
				if(end_detector == ";"){
					break; // if ';' is encountered, it is the end of polygon
				}
				myfile >> y_temp;
				x_temp = atoi(end_detector.c_str());
				polygon_temp.push_back(gtl::construct<Point>(x_temp,y_temp));
				//cout <<'a'<< x_temp << ' ' << y_temp << endl;
			}
			gtl::set_points(polygon, polygon_temp.begin(), polygon_temp.end());	// store into proper storage
			operation_set.push_back(polygon);	// store into polygon set structure
			cout << operation_set.size()<<'i' << endl;
			myfile >> end_detector;
			if(end_detector == "END"){
				//cout <<"END" << endl;
				break; // if "END" is encountered, it is the end of operation
			}
			else{
				//cout << end_detector << poly_step_n<<endl;
				poly_step_n ++;
				//continue;
			}
			
		}		
		
		Polygon_Set operation_merge; // first merge all polygons regardless of operation type
		gtl::clear(operation_merge);
		cout << operation_set.size()<<'j' << endl;
		//gtl::assign(operation_merge, operation_set);
		//cout << operation_merge.size() << 'h' << endl;
		
		if(this_operation[0] == 'M'){
			queue_merge.push_back(operation_set);
			//main_set += operation_merge;
			//cout <<"Merging"<<endl;
		}else if(this_operation[0] == 'C') {
			//main_set -= operation_merge;
			queue_clip.push_back(operation_set);
			//cout <<"Clipping"<<endl;
		}
		
		
		
//		for(int o = 0;o < operation_merge.size();o++){
//			Polygon::iterator_type it_start = gtl::begin_points(operation_merge[o]);
//			Polygon::iterator_type it_end = gtl::end_points(operation_merge[o]);
//			
//			do{
//			//cout <<o << ' '<< gtl::x(*it_start)<<' '<<gtl::y(*it_start) << endl;
//			//cout <<'w'<< *it_start_h<<' '<<gtl::y(*it_start_h) << endl;
//			if(it_start!=it_end)
//				it_start ++;
//			}while(it_start!=it_end);	
//		}
		
		//Polygon::iterator_holes_type it_start_h = gtl::begin_holes(main_set[0]);
		//Polygon::iterator_holes_type it_end_h = gtl::end_holes(main_set[0]);
		//		
		//		cout << "He is not handsome." << main_set[0].size_holes() << endl;
		//		
		//		const PolygonNoHoles& start_h = *it_start_h;
		//		//const PolygonNoHoles& end_h = *it_end_h;
		//		cout << "He is so handsome." << endl;

		//PolygonNoHoles::iterator_type it_start_h_QQ = gtl::begin_points(start_h);
		//PolygonNoHoles::iterator_type it_end_h_QQ = gtl::end_points(start_h);

	}
	
	for (operation_it = operation_list.begin(); operation_it != operation_list.end(); ++operation_it){
		string operation_queue = *operation_it ;
		char operation_type = operation_queue[0];
		operation_queue.erase(0,1);
		int operation_num = atoi(operation_queue.c_str());
		//cout <<operation_type<< "haha" << operation_num << typeid(operation_num).name() <<"\n";
		if (operation_type == 'M'){
			cout << "merging M" <<operation_num <<  endl; 
			main_set += queue_merge[operation_num-1];
			cout << main_set.size();
		}else if (operation_type == 'C'){
			cout << "cipping C" <<operation_num <<  endl; 
			main_set -= queue_clip[operation_num-1];
		}
	}
	
//	for (int n_poly = 0;n_poly < main_set.size(); n_poly ++){
//			Polygon res = main_set[n_poly];
//			Polygon::iterator_type it_start = gtl::begin_points(res);
//			Polygon::iterator_type it_end = gtl::end_points(res);
//			test_ce<gtl::connectivity_extraction_90<long long> >();
//	}
	cout << main_set.size()<<"distinct polygons" << endl;
	int mode = 3;
	gtl::orientation_2d orient_surrey_carry = gtl::orientation_2d();
	if(last_operation == "SH"){
		cout << "SH"<< endl;
		gtl::get_rectangles(rects, main_set, orient_surrey_carry);	
	}else if (last_operation == "SV"){
		cout << "SV" << endl;
		// gtl::orientation_2d_enum val;
		orient_surrey_carry.turn_90();
		gtl::get_rectangles(rects, main_set, orient_surrey_carry);		
	}else if (last_operation == "SO" && mode == 1){
		cout << "SO mode min(SV,SH)" << endl;
		// min (SV,SH)
		std::vector< gtl::rectangle_data<long long> > rects_compete;
		std::vector< gtl::rectangle_data<long long> > rects_compete_1;
		std::vector< gtl::rectangle_data<long long> > rects_compete_2;
		gtl::get_rectangles(rects, main_set, orient_surrey_carry);
		int n_rects_H = rects.size();
		orient_surrey_carry.turn_90();
		gtl::get_rectangles(rects_compete, main_set, orient_surrey_carry);
		int n_rects_V = rects_compete.size();
		if(n_rects_V < n_rects_H){
			rects = rects_compete;
		}
	}else if (last_operation == "SO" && mode == 2){
		cout << "SO mode 2" << endl;
		//min(SV,SH) of all
		std::vector< gtl::rectangle_data<long long> > rects_compete_1;
		std::vector< gtl::rectangle_data<long long> > rects_compete_2;
		int counter10 = 0;
		int counter100 = 0;
		int counter1000 = 0;
		int counter10000 = 0;
		int counter_ = 0;
		for(int n = 0; n <main_set.size();++n){
			if(main_set[n].size() < 7){
				counter10++;
				//continue;
			}else if(main_set[n].size() < 100){
				counter100++;
				//continue;
			}else if(main_set[n].size() < 1000){
				//counter1000++;
			}else if(main_set[n].size() < 10000){
				counter10000++;
				//continue;
			}else{
				counter_++;
				//continue;
			}
			rects_compete_1.clear();
			rects_compete_2.clear();
			gtl::get_rectangles(rects_compete_1, main_set[n], orient_surrey_carry);
			int n_rects_H = rects_compete_1.size();
			orient_surrey_carry.turn_90();
			gtl::get_rectangles(rects_compete_2, main_set[n], orient_surrey_carry);
			orient_surrey_carry.turn_90();
			int n_rects_V = rects_compete_2.size();
			if(n_rects_V < n_rects_H){
				rects.insert(rects.end(), rects_compete_2.begin(), rects_compete_2.end());		
			}else{
				rects.insert(rects.end(), rects_compete_1.begin(), rects_compete_1.end());		
			}			
		}
		cout << counter10 << ' ' << counter100 << ' ' << counter1000<< ' ' << counter10000 << ' ' << counter_ << ' '<<endl;		
	}else if (last_operation == "SO" && mode == 3){
		cout << "SO mode 3" << endl;
		Polygon_Set rects_remerge; // records the 
		std::vector< gtl::rectangle_data<long long> > rects_resplit;
		std::vector< gtl::rectangle_data<long long> > rects_compete_1;
		std::vector< gtl::rectangle_data<long long> > rects_compete_2;
		map<long long,list<long long> > node_from_x; // find nodes exist in O(1) time from dictionary 
		
		for(int n = 0; n <main_set.size();++n){ // for each disconnected set
			if(n%100==0){
				//cout << n << endl;
			}
			if(main_set[n].size() < 7){
				rects_compete_1.clear();
				gtl::get_rectangles(rects_compete_1, main_set[n], orient_surrey_carry);
				rects.insert(rects.end(), rects_compete_1.begin(), rects_compete_1.end());
			
				continue;
			}
//			if(main_set[n].size() < 1){
//				rects_compete_1.clear();
//				rects_compete_2.clear();
//				gtl::get_rectangles(rects_compete_1, main_set[n], orient_surrey_carry);
//				int n_rects_H = rects_compete_1.size();
//				orient_surrey_carry.turn_90();
//				gtl::get_rectangles(rects_compete_2, main_set[n], orient_surrey_carry);
//				orient_surrey_carry.turn_90();
//				int n_rects_V = rects_compete_2.size();
//				if(n_rects_V < n_rects_H){
//					rects.insert(rects.end(), rects_compete_2.begin(), rects_compete_2.end());
//				}else{
//					rects.insert(rects.end(), rects_compete_1.begin(), rects_compete_1.end());
//				}
//				continue;
//			}
			
			node_from_x.clear();
			rects_resplit.clear();
			rects_compete_1.clear();
			rects_compete_2.clear();
			Polygon::iterator_type it_start = gtl::begin_points(main_set[n]); // find ALL vertices of main_set[n], including holes
			Polygon::iterator_type it_end = gtl::end_points(main_set[n]);			
			do{
				//cout << 'o' << ' '<< gtl::x(*it_start)<<' '<<gtl::y(*it_start) << endl;
				//if ( node_go.find(tempkey) == node_go.end() )
				node_from_x[x(*it_start)].push_back(y(*it_start)); // find ALL vertices of main_set[n], this part finds outer
				it_start++;
			}while(it_start!=it_end);	
			Polygon::iterator_holes_type it_start_h = gtl::begin_holes(main_set[n]);
			Polygon::iterator_holes_type it_end_h = gtl::end_holes(main_set[n]);
			
			if(it_start_h == it_end_h){
				//cout << "no holes" <<endl;
			}else{
				const PolygonNoHoles& end_h = *it_end_h;
				do{
					const PolygonNoHoles& start_h = *it_start_h;
					
					PolygonNoHoles::iterator_type it_start_h_node = gtl::begin_points(start_h); // find ALL vertices of main_set[n], this part finds holes
					PolygonNoHoles::iterator_type it_end_h_node = gtl::end_points(start_h);	
	 				do{
						//cout << 'o' << ' '<< gtl::x(*it_start)<<' '<<gtl::y(*it_start) << endl;
						//if ( node_go.find(tempkey) == node_go.end() )
						//cout <<x(*it_start_h_node)<<' '<<y(*it_start_h_node)<<endl;
						node_from_x[x(*it_start_h_node)].push_back(y(*it_end_h_node));
						it_start_h_node++;
					}while(it_start_h_node!=it_end_h_node);
					it_start_h++;
				}while(it_start_h!=it_end_h);
				
			}
			
			
			//try split_V and split_H, use the smaller one as the main slicing method;
			gtl::get_rectangles(rects_compete_1, main_set[n], orient_surrey_carry); 
			int n_rects_H = rects_compete_1.size();
			
			orient_surrey_carry.turn_90();
			gtl::get_rectangles(rects_compete_2, main_set[n], orient_surrey_carry);
			orient_surrey_carry.turn_90();
			int n_rects_V = rects_compete_2.size();
			if(n_rects_V < n_rects_H){
				for(int rc = 0 ; rc < rects_compete_2.size();rc++){ // for each sliced rectangle, check if all 4 points are nodes;
					
					Rectangle checknode_poly = rects_compete_2[rc];
					int is_node = 0;
					long long x_low = gtl::xl(checknode_poly);
					long long y_low = gtl::yl(checknode_poly);
					long long x_high = gtl::xh(checknode_poly);
					long long y_high = gtl::yh(checknode_poly);
					list<long long> x_ls = node_from_x[x_low];
					for(list<long long>::iterator ls_it = x_ls.begin();ls_it != x_ls.end(); ++ls_it){
						if(y_low == *ls_it){
							is_node += 1;		
						}else if (y_high == *ls_it){
							is_node += 1;
						}
					}
					x_ls = node_from_x[x_high];
					for(list<long long>::iterator ls_it = x_ls.begin();ls_it != x_ls.end(); ++ls_it){
						if(y_low == *ls_it){
							is_node += 1;		
						}else if (y_high == *ls_it){
							is_node += 1;
						}
					}
					if (is_node !=4){ // some point is not node, add to slice list
						rects_resplit.push_back(checknode_poly) ;
					}else if (is_node ==4){ // all points are node, add to final list
						rects.push_back(checknode_poly);
					}
				}
				rects_remerge += rects_resplit; // merge the reslice list
				for (int rem = 0; rem < rects_remerge.size();++rem){ // for each polygon to be resliced, find the best of split_H, split_V
					rects_compete_1.clear();
					rects_compete_2.clear();
					gtl::get_rectangles(rects_compete_1, rects_remerge[rem], orient_surrey_carry);
					n_rects_H = rects_compete_1.size();
					orient_surrey_carry.turn_90();
					gtl::get_rectangles(rects_compete_2, rects_remerge[rem], orient_surrey_carry);
					n_rects_V = rects_compete_2.size();
					orient_surrey_carry.turn_90(); 
					if(n_rects_V < n_rects_H){
						rects.insert(rects.end(), rects_compete_2.begin(), rects_compete_2.end());	
					}else{
						rects.insert(rects.end(), rects_compete_1.begin(), rects_compete_1.end());	
					}
				}
				rects_remerge.clear();
						
			}else{
				for(int rc = 0 ; rc < rects_compete_1.size();rc++){
					
					Rectangle checknode_poly = rects_compete_1[rc];
					int is_node = 0;
					long long x_low = gtl::xl(checknode_poly);
					long long y_low = gtl::yl(checknode_poly);
					long long x_high = gtl::xh(checknode_poly);
					long long y_high = gtl::yh(checknode_poly);
					list<long long> x_ls = node_from_x[x_low];
					
					for(list<long long>::iterator ls_it = x_ls.begin();ls_it != x_ls.end(); ++ls_it){
						if(y_low == *ls_it){
							is_node += 1;		
						}else if (y_high == *ls_it){
							is_node += 1;
						}
					}
					
					x_ls = node_from_x[x_high];
					for(list<long long>::iterator ls_it = x_ls.begin();ls_it != x_ls.end(); ++ls_it){
						if(y_low == *ls_it){
							is_node += 1;		
						}else if (y_high == *ls_it){
							is_node += 1;
						}
					}
					
					if (is_node !=4){
						rects_resplit.push_back(checknode_poly);
					}else if (is_node ==4){
						rects.push_back(checknode_poly);
					}
					
					
				}
				
				rects_remerge += rects_resplit;
				//cout << "merged" << endl;
				//cout << rects_remerge.size() << endl;
				for (int rem = 0; rem < rects_remerge.size();++rem){
					
					rects_compete_1.clear();
					rects_compete_2.clear();
					gtl::get_rectangles(rects_compete_1, rects_remerge[rem], orient_surrey_carry);
					n_rects_H = rects_compete_1.size();
					orient_surrey_carry.turn_90();
					gtl::get_rectangles(rects_compete_2, rects_remerge[rem], orient_surrey_carry);
					n_rects_V = rects_compete_2.size();
					orient_surrey_carry.turn_90(); 
					if(n_rects_V < n_rects_H){
						rects.insert(rects.end(), rects_compete_2.begin(), rects_compete_2.end());	
					}else{
						rects.insert(rects.end(), rects_compete_1.begin(), rects_compete_1.end());	
					}
				}
				rects_remerge.clear();
				//cout << "done" << endl;
			}			
		}
	
	}
	ofstream outfile;
	cout << rects.size()<<" rectangles"<<endl;
	
	
	outfile.open(argv[2]);
	for(int r = 0; r < rects.size();r++){
		outfile << "RECT " << gtl::xl(rects[r])<<' '<<gtl::yl(rects[r])<<' '<<gtl::xh(rects[r])<<' '<<gtl::yh(rects[r])<<" ;"  << endl;
	}
	
	

}
