#pragma once
#include <string>
#include <vector>
namespace WorldGen
{
	template < class T >
	class Wrapper
	{
	public:
		T* Create()
		{
			int newId = NextId;
			++NextId;
			return Create( newId );
		}

		T* Create( int NewId )
		{
			if ( GetItemById( NewId ) == nullptr )
				Data.push_back( new T( NewId ) );
			return GetItemById( NewId );
		}

		void Remove( int Id )
		{
			for ( int Idx = 0; Idx < Data.size(); ++Idx )
			{
				if ( Data[ Idx ]->Id_ == Id )
				{
					Data.erase(Data.begin() + Idx);
					return;
				}
			}
		}

		T* GetItemById( int Id )
		{
			for ( unsigned int Idx = 0; Idx < Data.size(); ++Idx )
			{
				if ( Data[ Idx ]->Id_ == Id )
				{
					return Data[ Idx ];
				}
			}
			return nullptr;
		}

		T* GetItem( int Pos )
		{
			return Data[ Pos ];
		}

		int Size()
		{
			return Data.size();
		}

	private:
		std::vector< T* > Data;
		int NextId;
	};

	class Data
	{
	public:
		Data( int Id , std::string ClassName );

		int Id_;

		std::string ToString();
	private: 
		std::string ClassName_;
	};

	class Room
		: public Data
	{
	public:
		Room( int Id );
		bool MurderRoom_;
	};

	class Person
		: public Data
	{
	public:
		Person( int Id );
		int InformationId_;
	};

	class Time
		: public Data
	{
	public:
		Time( int Id );
	};

	class Information
		: public Data
	{
	public:
		Information( int Id );
		int StartTimeId_;
		int EndTimeId_;
		int PersonId_;
		int RoomId_;
	};

	class Murder
		: public Data
	{
	public:
		Murder( int Id );
		int RoomId_;
		int TimeId_;
		int PersonId_;
	};

}