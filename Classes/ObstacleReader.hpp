//
//  ObstacleReader.hpp
//  FlappyBird
//
//  Created by Shuhei Asada on 2016/05/12.
//
//

#ifndef ObstacleReader_hpp
#define ObstacleReader_hpp

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class ObstacleReader : public cocostudio::NodeReader
{
public:
    static ObstacleReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* ObstacleReader_hpp */
