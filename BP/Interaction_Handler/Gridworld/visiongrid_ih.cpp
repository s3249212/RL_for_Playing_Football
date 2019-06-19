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

bool VisionGrid_IH::isInVisionGrid(int x, int y, int* xIdx, int* yIdx){
    int agentX = agents[0]->getX(), agentY = agents[0]->getY();

    if(!(x < agentX - layerBounds[0] &&
            x >= agentX + layerBounds[nLayerBounds - 1] &&
            y < agentY - layerBounds[0] &&
            y >= agentY + layerBounds[nLayerBounds - 1])){
        return false;
    }

    for(*xIdx = 0; *xIdx < nLayerBounds - 2; *xIdx++){
        if(x < agentX - layerBounds[*xIdx] &&
                x >= agentX + layerBounds[*xIdx + 1]){
            break;
        }
    }

    for(*yIdx = 0; *yIdx < nLayerBounds - 2; *yIdx++){
        if(y < agentY - layerBounds[*yIdx] &&
                y >= agentY + layerBounds[*yIdx + 1]){
            break;
        }
    }

    return true;
}

int VisionGrid_IH::getGridArea(int xIdx, int yIdx){
    int xLayer, yLayer;
    int centreIdx = nLayerBounds / 2 - 1;
    xLayer = xIdx < centreIdx? centreIdx - xIdx: xIdx - centreIdx;
    yLayer = yIdx < centreIdx? centreIdx - yIdx: yIdx - centreIdx;
    int width = gridSizes[xLayer];
    int height = gridSizes[yLayer];
    return width * height;
}

int VisionGrid_IH::getInputIdx(int xIdx, int yIdx, int offset, int nDepth){
    int inputPixelIdx = (nLayerBounds - 1) * yIdx + xIdx
            + ((yIdx == nLayerBounds / 2 - 1 && xIdx > nLayerBounds / 2 - 1) || yIdx > nLayerBounds / 2 - 1);

    return nDepth * inputPixelIdx + offset;
}

void VisionGrid_IH::addHorizontalLineToGrid(int x0, int x1, int y, int offset, int nDepth){

}

void VisionGrid_IH::addVerticalLineToGrid(int y0, int y1, int x, int offset, int nDepth){

}

void VisionGrid_IH::addLineToGrid(int x0, int y0, int x1, int y1, int offset, int nDepth){
    if(x0 - x1 != 0 && y0 - y1 != 0){
        cout << "Does not work with diagonal lines" << endl;
        exit(-1);
    }

    if(x0 - x1 == 0){
        addVerticalLineToGrid(y0, y1, x0, offset, nDepth);
    }

    if(y0 - y1 == 0){
        addHorizontalLineToGrid(x0, x1, y0, offset, nDepth);
    }
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

    int xIdx, yIdx;

    vector<Gridworld_Agent*> agents = world->getAgents();

    for(Gridworld_Agent* agent: agents){
        if(isInVisionGrid(agent->getX(), agent->getY(), &xIdx, &yIdx)){
            int offset = agent->getTeam() == team? sameTeamIdx: opponentIdx;
            int inputIdx = getInputIdx(xIdx, yIdx, offset, nDepth);
            int area = getGridArea(xIdx, yIdx);
            (*input)[inputIdx] += 1.0 / area;
        }
    }

    if(isInVisionGrid(world->getBall()->getX(), world->getBall()->getY(), &xIdx, &yIdx)){
        int offset = ballIdx;
        int inputIdx = getInputIdx(xIdx, yIdx, offset, nDepth);
        int area = getGridArea(xIdx, yIdx);
        (*input)[inputIdx] += 1.0 / area;
    }



    return *input;
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
