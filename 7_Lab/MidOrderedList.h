
#ifndef MIDORDEREDLIST_H
#define MIDORDEREDLIST_H

template <class T> 
class MidOrderedList: protected OrderedList {

	public:
		MidOrderedList() : OrderedList()
		{}
		~MidOrderedList() : ~OrderedList()
		{}

		void additem(T in){

			if (size == 25){
				throw ListFullException();
			}

			int mid = size/2;
			int insertIndex;					//        0 1 2 3 4 5 6 7 8 9 
				
			T* inp = new T(in);							//        1 3 5 7 14 15 16 17 18 19

			//all values above insert index move up
			if (in > *(arr[mid])){
				int i = mid;

				while (in > *(arr[i])){
					insertIndex = i + 1;
					i = i + 1;

					if (i > mid*2){
						insertIndex = size;
						break;
					}
				}
			};

			if (in < *(arr[mid]))
			{
				int i = mid;

				while (in < *(arr[i])){
					insertIndex = i - 1;
					i = i - 1;

					if (i < 0){
						insertIndex = 0;
						break;
					}
				}
			}

			for (int j = size - 1; j > insertIndex - 1; j--){
				arr[j + 1] = arr[j];
			};
			arr[insertIndex] = inp;
		}
};







#endif