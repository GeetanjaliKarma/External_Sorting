#include <bits/stdc++.h>

using namespace std;
#define pb push_back

class Page{
    int maxNumOfRecords;
    int availableRecords;
    int* array;
    friend class File;
public:
    Page(int recordsPerPage){
        array = new int[recordsPerPage];
        maxNumOfRecords = recordsPerPage;
        availableRecords = 0;
    }

    int availableRecordsInPage(){
        return availableRecords;
    }
};

class File{/home/k.geetanjali/Downloads/code-stable-x64-1648620864

    deque<Page*> pagesPtr;
public:
    void insertPagePtr(Page* page){
        pagesPtr.pb(page);
    }

    Page* pointToPage(int pageIndex){
        return pagesPtr[pageIndex];
    }

    void insertInPage(Page* currentPage, int posToInsert, int numToInsert){
        currentPage->array[posToInsert] = numToInsert;
        currentPage->availableRecords++;
    }

    void extSort(int B){
        int pass = 0;
        while(pagesPtr.size() > 1){
            internalSort(pass, B);

            pass++;
        }

    }

    void internalSort( int pass, int B){
        if(pass == 0){
            int pageCount = 0;
            int initialPagesPtrSize = pagesPtr.size();
            int maxRecordsInNewPage = pagesPtr[0] -> maxNumOfRecords;

            vector<int> temp;
            while(pageCount <= initialPagesPtrSize){
                //If pageCount % B == 0, then insert elements of sorted temp array in newPages.
                if(pageCount % B == 0 || pageCount == initialPagesPtrSize){
                    //sort temp array
                    sort(temp.begin(), temp.end());

                    //create new pages whenever previous page is full
                        //insert the newPage in pagesPtr
                        //insert the element in new page
                    int i = 0;
                    Page* currentPagePtr;
                    while(i < temp.size()){

                        if(i % maxRecordsInNewPage == 0){
                            Page* newPage = new Page(maxRecordsInNewPage);
                            currentPagePtr = newPage;
                            pagesPtr.pb(newPage);
                        }

                        insertInPage(currentPagePtr, i % maxRecordsInNewPage, temp[i]);
                        i++;

                    }

                    temp.clear();
                }

                if(pageCount != initialPagesPtrSize){
                    //Otherwise, add the elemets of pagesPtr[0] to temp array.
                    for(int i = 0; i < pagesPtr[0]->availableRecordsInPage(); i++){
                        temp.pb(pagesPtr[0]->array[i]);
                    }

                    //delete the array which is pointed by pagesPtr[0] -> array;
                    //remove its pointer from pagesPtr deque.
                    delete pagesPtr[0] -> array;
                    pagesPtr.pop_front();
                }

                //Go to the next page
                pageCount++;
            }
        }else{
            //For pass = 1,2,3...... do this :-
            int pageCount = 0;
            int initialPagesPtrSize = pagesPtr.size();

            int numOfPagesToBeMerged = (B - 1);
            int maxRecordsInNewPage = numOfPagesToBeMerged * (pagesPtr[0] -> maxNumOfRecords);

            vector<int> temp;
            while(pageCount <= initialPagesPtrSize){
                //If pageCount % B == 0, then insert elements of sorted temp array in newPages.
                if(pageCount % numOfPagesToBeMerged == 0 || pageCount == initialPagesPtrSize){
                    //sort temp array
                    sort(temp.begin(), temp.end());

                    //create new pages whenever previous page is full
                        //insert the newPage in pagesPtr
                        //insert the element in new page
                    int i = 0;
                    Page* currentPagePtr;
                    while(i < temp.size()){

                        if(i % maxRecordsInNewPage == 0){
                            Page* newPage = new Page(maxRecordsInNewPage);
                            currentPagePtr = newPage;
                            pagesPtr.pb(newPage);
                        }

                        insertInPage(currentPagePtr, i % maxRecordsInNewPage, temp[i]);
                        i++;

                    }
                    temp.clear();
                }
                
                if(pageCount != initialPagesPtrSize){
                    //Otherwise, add the elemets of pagesPtr[0] to temp array.
                    for(int i = 0; i < pagesPtr[0]->availableRecordsInPage(); i++){
                        temp.pb(pagesPtr[0]->array[i]);
                    }

                    //delete the array which is pointed by pagesPtr[0] -> array;
                    //remove its pointer from pagesPtr deque.
                    delete pagesPtr[0] -> array;
                    pagesPtr.pop_front();
                }
                //Go to the next page
                pageCount++;
            }
        }
        return;
    }

    void showStatus(){
        int i = 0;
        while(i < pagesPtr[0]->availableRecordsInPage()){
            cout<<pagesPtr[0]->array[i]<<endl;
            i++;
        }
    }
};

int main(){
    int B;  //Available Buffer Pages
    cin>>B;

    int numOfRecordsPerPage;
    cin>>numOfRecordsPerPage;

    int totalNumOfRecords;
    cin>>totalNumOfRecords;

    int numOfPages = (totalNumOfRecords / numOfRecordsPerPage);
    //Number of pages required is equal to (totalNumOfRecords/numOfRecordsPerPage)
    (totalNumOfRecords % numOfRecordsPerPage) > 0 ? numOfPages += 1 : numOfPages = numOfPages;

    File file;

    for(int i = 0; i < numOfPages; i++){
        Page* newPage = new Page(numOfRecordsPerPage);
        file.insertPagePtr(newPage);
    }

    int cnt = 0;
    Page* currentPagePtr;
    for(int i = 0; i < totalNumOfRecords; i++){
        if(cnt % numOfRecordsPerPage == 0){
            int pageIndex = cnt / numOfRecordsPerPage;
            currentPagePtr = file.pointToPage(pageIndex);
        }

        int numToInsert;
        cin>>numToInsert;

        file.insertInPage(currentPagePtr, cnt % numOfRecordsPerPage, numToInsert);
        cnt++;
    }

    file.extSort(B);
    file.showStatus();

    return 0;
}
// #include <bits/stdc++.h>
// using namespace std;

// void merge(vector<vector<int>> &runs, vector<int> &temp)
// {
//     vector<int> pointer;
//     int num = 0;
//     for (int i = 0; i < runs.size(); i++)
//     {
//         pointer.push_back(0);
//         num += runs[i].size();
//     }

//     for (int i = 0; i < num; i++)
//     {
//         int min = INT_MAX;
//         int k = 0;
//         for (int j = 0; j < pointer.size(); j++)
//         {
//             if (pointer[j] < runs[j].size() && runs[j][pointer[j]] < min)
//             {
//                 min = runs[j][pointer[j]];
//                 k = j;
//             }
//         }
//         temp.push_back(min);
//         pointer[k]++;
//     }
// }

// void external_sort(vector<vector<int>> &runs, int B)
// {
//     // Intially sorting each page
//     for (int i = 0; i < runs.size(); i++)
//     {
//         sort(runs[i].begin(), runs[i].end());
//     }

//     while (runs.size() > 1)
//     {
//         vector<vector<int>> newruns;
//         int k = 0;
//         int i = 0;
//         while (i < runs.size())
//         {
//             vector<vector<int>> temp;
//             for (k = 0; k < B - 1 && i + k < runs.size(); k++)
//             {
//                 temp.push_back(runs[i + k]);
//             }
//             vector<int> temp1;
//             // Merging B-1 runs
//             merge(temp, temp1);
//             newruns.push_back(temp1);
//             i += k;
//         }
//         runs = newruns;
//     }
// }

// int main()
// {
//     int B, rec_page, records;
//     cin >> B >> rec_page >> records;
//     vector<vector<int>> runs;
//     int k = 0;
//     int i = 0;
//     while (i < records)
//     {
//         vector<int> v;
//         for (k = 0; k < rec_page && i + k < records; k++)
//         {
//             int a;
//             cin >> a;
//             v.push_back(a);
//         }
//         runs.push_back(v);
//         i += k;
//     }

//     external_sort(runs, B);
//     for (int i = 0; i < runs[0].size(); i++)
//     {
//         cout << runs[0][i] << endl;
//     }
//     return 0;
// }
