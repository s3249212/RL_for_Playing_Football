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
    nInput = ((2 * n + 1) * (2 * n + 1) - 1) * l;
    int nActions = 18;
    MLPQPlayer->initialize(nInput, nActions);

    input = new vector<double>(nInput, 0);

    nLayerBounds = 2 * (gridSizes.size() + 1);
    layerBounds = new int[nLayerBounds];

    int lIdx = nLayerBounds / 2 - 1;
    int rIdx = nLayerBounds / 2;

    layerBounds[lIdx] = 0;
    layerBounds[rIdx] = 1;

    for(int g: gridSizes){
        lIdx--;
        rIdx++;
        layerBounds[lIdx] = layerBounds[lIdx + 1] - g;
        layerBounds[rIdx] = layerBounds[rIdx - 1] + g;
    }
}

bool isInVisionGrid(int x, int y, int* xIdx, int* yIdx){

}

vector<double> VisionGrid_IH::generateInput()
{
    for(int i = 0; i < nInput; i++){
        (*input)[i] = 0;
    }

    int agentX = agents[0]->getX(), agentY = agents[0]->getY();

    int nDepth = 6;
    int sameTeamIdx = 0;
    int opponentIdx = 1;
    int ballIdx = 2;
    int wallIdx = 3;
    int ownGoalIdx = 4;
    int opponentGoalIdx = 5;

    vector<Gridworld_Agent*> agents = world->getAgents();

    for(Gridworld_Agent* agent: agents){
        if(agent->getX() < agentX - layerBounds[0] &&
                agent->getX() >= agentX + layerBounds[nLayerBounds - 1] &&
                agent->getY() < agentY - layerBounds[0] &&
                agent->getY() >= agentY + layerBounds[nLayerBounds - 1]){
            int xIdx, yIdx;

            for(xIdx = 0; xIdx < nLayerBounds - 2; xIdx++){
                if(agent->getX() < agentX - layerBounds[xIdx] &&
                        agent->getX() >= agentX + layerBounds[xIdx + 1]){
                    break;
                }
            }

            for(yIdx = 0; yIdx < nLayerBounds - 2; yIdx++){
                if(agent->getY() < agentY - layerBounds[yIdx] &&
                        agent->getY() >= agentY + layerBounds[yIdx + 1]){
                    break;
                }
            }

            int inputPixelIdx = (nLayerBounds - 1) * yIdx + xIdx
                    + ((yIdx == layerBounds / 2 && xIdx > layerBounds / 2) || yIdx > layerBounds / 2);

            int inputIdx = nDepth * inputPixelIdx + (agent->getTeam() == team? sameTeamIdx: opponentIdx);
        }
    }


/*
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
   */
}
