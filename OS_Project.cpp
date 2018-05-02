#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <queue>
#include <set>

#include <math.h>

#define MAX 199 // max value of cylinder

using namespace std;


queue<int> Q;
set<int> s;
vector<int> dis;  		   	// distance
vector<int> order; 			// order
int cost; 					// sum cost
vector<int> listInput;		// print Input

void ReadData()
{
	cout << "\nInput cylinders want to access (Enter -1 to end): "; 
	int cld; cin >> cld;
	while( cld != -1 )
	{
		Q.push(cld);
		s.insert(cld);
		listInput.push_back(cld);
		cin >> cld;
	} 

}

void ReadData(char* filename)
{
	cout << "Reading Data from file...  ";
	ifstream f (filename);

	int cld; f >> cld;
	while( cld != -1 )
	{
		Q.push(cld);
		s.insert(cld);
		listInput.push_back(cld);
		f >> cld;
	}
	
	cout << "done!\n";
}



void init()
{
	cost = 0;
	dis.clear();
	order.clear();
	
}

void PrintRezult ( vector<int> listInput, vector<int> order, vector<int> dis, int cost  )
{
	
	cout << " Input: ";
	for(int i = 0; i <= listInput.size() -1 ; i++ )
		cout << listInput[i] << "   ";
	
	cout << "\n Order: ";
	for( int i = 0; i <= order.size() - 2; i++)
		printf("%3d --> ",order[i]);
	cout << order[order.size() - 1];
	
	cout << "\n Cost :    ";
	for( int i = 0; i <= dis.size() -1; i++)
		printf(" %3d    ",dis[i]);
		
	cout << "\n Sum of cost: " << cost;
}

void FCFS( queue<int> Q )
{
	init();
	cout << "\n\nFCFS:\n";
	int cur = Q.front(); Q.pop();
	order.push_back(cur);
	
	bool flag = false;
	char ch; 

	while( !Q.empty() )
	{
		int cld = Q.front(); Q.pop();
		order.push_back( cld );
		int d = abs( cld - cur );
		dis.push_back( d );
		cur = cld;
		cost += d;		
	}
	PrintRezult( listInput, order, dis, cost );
	

}


void SSTF( set<int> s )
{
	init();
	cout << "\n\nSSTF:\n";
	set<int>::iterator cur = s.find( listInput[0] ); order.push_back(*cur);
	int d, d_pre, d_post;
	while( !s.empty() )
	{
		if( cur == s.begin() && cur == --s.end() )
			break;
		else if( cur == s.begin() && cur != --s.end() )
		{
			set<int>::iterator post = next(cur,1);
			order.push_back( *post );
			d = *post - *cur;
			dis.push_back( d );
			cost += d;
			
			s.erase( cur );
			cur = post;
		}
		else if( cur == --s.end() && cur != s.begin() )
		{
			set<int>::iterator pre = prev(cur,1);
			order.push_back( * pre );
			d = * cur - *pre;
			dis.push_back( d );
			cost += d;
			
			s.erase( cur );
			cur = pre;
		}
		else
		{
			set<int>::iterator pre = prev(cur,1);
			set<int>::iterator post = next(cur,1);
			
			d_pre = *cur - *pre;
			d_post = *post - *cur;
			
			if( d_pre < d_post )
			{
				order.push_back( *pre );
				dis.push_back( d_pre );
				cost += d_pre;
				
				s.erase ( cur );
				cur = pre;
			}
			else
			{
				order.push_back( *post );
				dis.push_back( d_post );
				cost+= d_post;
				
				s.erase( cur );
				cur = post;
			}
		}	
				
	}
	
	PrintRezult( listInput, order, dis, cost );
}

void SCAN( set<int> s )
{
	cout << "\n\nSCAN:\n";
	init();
	
	s.insert(0);
	
	set<int>::iterator base = s.find( listInput[0] );
	order.push_back( *base );
	
	set<int>::iterator cur = base;
	for( set<int>::iterator it = prev(base,1); it != prev( s.begin() ); it-- )
	{
		int now = *it;
		order.push_back( now );
		int d = *cur - now;
		dis.push_back( d );
		cost+=d;
		cur = it;
	}
	

	for( set<int>::iterator it = next(base,1); it != s.end(); it++ )
	{
		int now = *it;
		order.push_back( now );
		int d =  now - *cur;
		dis.push_back( d );
		cost += d;
		cur = it;
	}
	
	PrintRezult( listInput, order, dis, cost );
	
}

//void CSCAN( set<int> s )
//{
//	cout << "\n\nCSCAN:\n";
//	init();
//	
//	s.insert(0);
//	s.insert(199);
//	
//	set<int>::iterator first = s.find( listInput[0] ); order.push_back( *first );
//	
//	set<int>::iterator initial = next(first,1);
//	int cur = *first;
//	s.erase( first );
//	
//	while( !s.empty() )
//	{
//		for( set<int>::iterator it = initial; it != s.end(); it++  )
//		{
//			set<int>::iterator temp = it;
//			int now = *it;
//			int d = abs( now - cur );
//			order.push_back( now );
//			dis.push_back( d );
//			cost+=d;
//			
//			cur = now; s.erase( temp );
//		}
//		initial = s.begin();		
//	}
//	
//	PrintRezult( listInput, order, dis, cost );
//	
//}


void CSCAN( set<int> s )
{
	cout << "\n\nCSCAN:\n";
	init();
	
	s.insert(0);
	s.insert(MAX);
	
	set<int>::iterator base = s.find( listInput[0] );
	order.push_back( *base );
	
	set<int>::iterator cur = base;
	for( set<int>::iterator it = next(base,1); it != s.end(); it++ )
	{
		int now = *it;
		order.push_back( now );
		int d =  abs(now - *cur);
		dis.push_back( d );
		cost += d;
		cur = it;
	}
	
	for( set<int>::iterator it = s.begin(); it != base ; it++ )
	{
		int now = *it;
		order.push_back( now );
		int d = abs(*cur - now);
		dis.push_back( d );
		cost+=d;
		cur = it;
	}
	
	PrintRezult( listInput, order, dis, cost );
	
}


void LOOK( set<int> s )
{
	cout << "\n\nLOOK:\n";
	init();
		
	set<int>::iterator base = s.find( listInput[0] );
	order.push_back( *base );
	
	set<int>::iterator cur = base;
	for( set<int>::iterator it = prev(base,1); it != prev( s.begin() ); it-- )
	{
		int now = *it;
		order.push_back( now );
		int d = *cur - now;
		dis.push_back( d );
		cost+=d;
		cur = it;
	}
	

	for( set<int>::iterator it = next(base,1); it != s.end(); it++ )
	{
		int now = *it;
		order.push_back( now );
		int d =  now - *cur;
		dis.push_back( d );
		cost += d;
		cur = it;
	}
	
	PrintRezult( listInput, order, dis, cost );
	
}

void CLOOK( set<int> s )
{
	cout << "\n\nCLOOK:\n";
	init();
		
	set<int>::iterator base = s.find( listInput[0] );
	order.push_back( *base );
	
	set<int>::iterator cur = base;
	for( set<int>::iterator it = next(base,1); it != s.end(); it++ )
	{
		int now = *it;
		order.push_back( now );
		int d =  abs(now - *cur);
		dis.push_back( d );
		cost += d;
		cur = it;
	}
	
	for( set<int>::iterator it = s.begin(); it != base ; it++ )
	{
		int now = *it;
		order.push_back( now );
		int d = abs(*cur - now);
		dis.push_back( d );
		cost+=d;
		cur = it;
	}
	
	PrintRezult( listInput, order, dis, cost );
	
}





int main()
{
//	ReadData();
	ReadData( "Input.txt" );
//	FCFS( Q );
//	SSTF( s );
//	SCAN( s );
//	CSCAN( s );
//	LOOK ( s );
	CLOOK (	s );

 printf("\n\nHello World\n");
 return 0;
}
