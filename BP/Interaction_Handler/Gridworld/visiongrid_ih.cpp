#include <array>
#include <string>
#include <vector>

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
    nInput = (2 * n + 1) * (2 * n + 1) * l;
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
    gridSizes.insert(gridSizes.begin(), 1);
}

bool VisionGrid_IH::isXorYInVisionGrid(int value, int centre, int* idx){
    if(value < centre + layerBounds[0] ||
            value >= centre + layerBounds[nLayerBounds - 1]){
        return false;
    }

    for(*idx = 0; *idx < nLayerBounds - 2; (*idx)++){
        if(value >= centre + layerBounds[*idx] &&
                value < centre + layerBounds[*idx + 1]){
            break;
        }
    }

    return true;
}

bool VisionGrid_IH::isXInVisionGrid(int x, int* xIdx){
    int agentX = agents[0]->getX();
    return isXorYInVisionGrid(x, agentX, xIdx);
}

bool VisionGrid_IH::isYInVisionGrid(int y, int* yIdx){
    int agentY = agents[0]->getY();
    return isXorYInVisionGrid(y, agentY, yIdx);
}

bool VisionGrid_IH::isInVisionGrid(int x, int y, int* xIdx, int* yIdx){
    return isXInVisionGrid(x, xIdx) && isYInVisionGrid(y, yIdx);
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
    int inputPixelIdx = (nLayerBounds - 1) * yIdx + xIdx;
            //+ ((yIdx == nLayerBounds / 2 - 1 && xIdx > nLayerBounds / 2 - 1) || yIdx > nLayerBounds / 2 - 1);

    return nDepth * inputPixelIdx + offset;
}

void VisionGrid_IH::addHorizontalLineToGrid(int x0, int x1, int y, int offset, int nDepth){
    int xIdx = 0, yIdx = 0;

    if(!isXInVisionGrid(y, &yIdx)){
        return;
    }

    int minX = x0 < x1? x0: x1;
    int maxX = x0 < x1? x1: x0;

    //int y = y > agents[0]->getY() + layerBounds[0]? y: agents[0]->getY() + layerBounds[0];
    int agentX = agents[0]->getX();

    while(xIdx < nLayerBounds && minX >= layerBounds[xIdx + 1] + agentX){
        xIdx++;
    }

    while(xIdx < nLayerBounds - 1 && maxX >= layerBounds[xIdx] + agentX){
        if(minX < layerBounds[xIdx] + agentX){
            minX = layerBounds[xIdx] + agentX;
        }
        int nextX = maxX < layerBounds[xIdx + 1] + agentX - 1? maxX: layerBounds[xIdx + 1] + agentX - 1;
        int nBlocksInside = nextX - minX + 1;
        int inputIdx = getInputIdx(xIdx, yIdx, offset, nDepth);
        int area = getGridArea(xIdx, yIdx);
        (*input)[inputIdx] += static_cast<double>(nBlocksInside) / area;
        xIdx++;
    }
}

void VisionGrid_IH::addVerticalLineToGrid(int y0, int y1, int x, int offset, int nDepth){
    int xIdx = 0, yIdx = 0;

    if(!isXInVisionGrid(x, &xIdx)){
        return;
    }

    int minY = y0 < y1? y0: y1;
    int maxY = y0 < y1? y1: y0;

    //int y = y > agents[0]->getY() + layerBounds[0]? y: agents[0]->getY() + layerBounds[0];
    int agentY = agents[0]->getY();

    while(yIdx < nLayerBounds && minY >= layerBounds[yIdx + 1] + agentY){
        yIdx++;
    }

    while(yIdx < nLayerBounds - 1 && maxY >= layerBounds[yIdx] + agentY){
        if(minY < layerBounds[yIdx] + agentY){
            minY = layerBounds[yIdx] + agentY;
        }
        int nextY = maxY < layerBounds[yIdx + 1] + agentY - 1? maxY: layerBounds[yIdx + 1] + agentY - 1;
        int nBlocksInside = nextY - minY + 1;
        int inputIdx = getInputIdx(xIdx, yIdx, offset, nDepth);
        int area = getGridArea(xIdx, yIdx);
        (*input)[inputIdx] += static_cast<double>(nBlocksInside) / area;
        yIdx++;
    }
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

    int width = world->getWidth();
    int height = world->getHeight();
    addLineToGrid(0, 0, width - 1, 0, wallIdx, nDepth);
    addLineToGrid(0, 1, 0, height - 1, wallIdx, nDepth);
    addLineToGrid(1, height - 1, width - 1, height - 1, wallIdx, nDepth);
    addLineToGrid(width - 1, 1, width - 1, height - 2, wallIdx, nDepth);

    int minGoalY = world->getHeight() / 2 - world->getGoalLength() + world->getHeight() % 2;
    int maxGoalY = minGoalY + 2 * world->getGoalLength() - world->getHeight() % 2;
    addLineToGrid(0, minGoalY, 0, maxGoalY, team == 0? ownGoalIdx: opponentGoalIdx, nDepth);
    addLineToGrid(width - 1, minGoalY, width - 1, maxGoalY, team == 0? opponentGoalIdx: ownGoalIdx, nDepth);

    /*for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            cout << "(";
            for(int k = 0; k < 6; k++){
                cout << (*input)[getInputIdx(j, i, k, 6)] << "\t";
            }
            cout << ")\t";
        }
        cout << endl;
    }
    cout << endl;*/

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
