/*
 * RoomStatues.h
 *
 *  Created on: Oct 6, 2012
 *      Author: xmuweili
 */

#ifndef ROOMSTATUES_H_
#define ROOMSTATUES_H_
#include<iostream>
#include<assert.h>

class RoomStatues{

private:
	int m_room_number;
	int m_support_date;
	bool *m_room_statues;

public:
	//room_number is the rooms hotel has
	//support date means how long the statues be recorded, default is 100 days, start from 10/01/2012
	RoomStatues(int room_number, int support_date = 100){
		m_support_date = support_date;
		m_room_statues = new bool[room_number  * support_date];

		//initialize all statues to be true
		for(int i=0; i<room_number  * support_date; ++i)
			m_room_statues[i] = true;

		std::cout<<"successful create rooms statues support "<<support_date<<" days at most!!\n";
	};
	~RoomStatues(){delete m_room_statues;};

	bool isRoomAvaible(int _room_num, int _start_day, int _end_day){
		assert(_start_day < m_support_date && _end_day < m_support_date);
		bool res_avi;
		for(int i=_room_num * m_support_date +_start_day;
				i<=_room_num * m_support_date +_end_day; ++i){
			if(!m_room_statues[i]){
				res_avi = false;
				break;
			}
		}
		return res_avi;
	};
};

#endif /* ROOMSTATUES_H_ */
