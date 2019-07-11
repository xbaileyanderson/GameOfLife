#ifndef START_H
#define START_H


class Start
{
    public:
        Start();
        virtual ~Start();
        void StartLife();
        void PromptFile();
        void PromptCoordinates();

        int x;
        int y;
        double popDensity;
    protected:
    private:
};

#endif // START_H
