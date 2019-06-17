#include "visiongrid_ih.h"

VisionGrid_IH::VisionGrid_IH(Gridworld* gridworld, MLPQ* player, int team, vector<int> gridSizes)
{
    this->world = gridworld;
    this->MLPQPlayer = player;
    this->player = player;
    this->team = team;
    this->gridSizes = gridSizes;
}


void VisionGrid_IH::initialize()
{
    int n = gridSizes.size();
    int l = 6;
    int nInput = ((2 * n + 1) * (2 * n + 1) - 1) * l;
    int nActions = 18;
    MLPQPlayer->initialize(nInput, nActions);
}

vector<double> VisionGrid_IH::generateInput()
{
   vector<double> input;

   array<int, 2> agentCoord = agents[0]->getCoord();

   int n = gridSizes.size();

   int sumSizes = 0;
   for(int size: gridSizes){
       sumSizes += size;
   }
   int startX = agentCoord[0] - sumSizes, startY = agentCoord[1] - sumSizes;

   vector<int> sizes = gridSizes;
   sizes.insert(sizes.cbegin(), 1);

   int curStartX = startX;
   for(int u = -n; u <= n; u++){
       int curStartY = startY;
       int width = sizes[abs(u)];
       for(int v = -n; v <= n; v++){
           int height = sizes[abs(v)];

           if(u != 0 || v != 0){
               array<int, 6> sum = {0, 0, 0, 0, 0, 0};
               for(int x = startX; x < startX + width; x++){
                   for(int y = startY; y < startY + height; y++){
                       array<bool, 6> currentPixel = world->getPixelData({x, y}, team);
                       for(int i = 0; i < 6; i++){
                           sum[i] += currentPixel[i];
                       }
                   }
               }

               array<double, 6> averages;
               for(int i = 0; i < 6; i++){
                   averages[i] = sum[i] / 6.0;
                   input.push_back(averages[i]);
               }
           }

           curStartY += height;
       }
       curStartX += width;
   }
   return input;
}
