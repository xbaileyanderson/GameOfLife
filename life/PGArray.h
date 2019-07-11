#ifndef PGARRAY_H
#define PGARRAY_H


class PGArray
{
    public:
        PGArray(int coodx, int coody, double density, int** fileArray, int mode, int Bool);
        virtual ~PGArray();
        //int **arr1 = 0;
       // int **arr2 = 0;

        int** MakeArr1();
        int** MakeArr2();

        void Print(int** array3);
        void PrintOutput(int** array420);
        void Clone(int** original, int ** clone);
        void ClassicMode(int** classicArr, int** cloneArr);
        void MirrorMode(int** mirrorArr, int** cloneArr2);
        void DonutMode(int ** donutArr, int** cloneArr3);
        void Play();
        void PlayOutput();
        void Enter();
        void Choose();
        int MatchArrays(int** array6, int** array9);
        void Initialize();
        void Initialize2();
        void GensStabilized();
        void Delay();


    protected:
    private:

};

#endif // PGARRAY_H
