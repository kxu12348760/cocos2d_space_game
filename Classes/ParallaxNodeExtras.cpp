#include "ParallaxNodeExtras.h"
#include <android/log.h>

#define  LOG_TAG    "parallax_node_extras"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

class PointObject : public Ref {
   public:
       inline void setRation(Point ratio) {_ratio = ratio;}
       inline void setOffset(Point offset) {_offset = offset;}
       inline void setChild(Node *var) {_child = var;}
       inline Point getOffset() const {return _offset;}
       inline Node* getChild() const {return _child;}
   private:
       Point _ratio;
       Point _offset;
       Node* _child;
};

ParallaxNodeExtras::ParallaxNodeExtras() {
    ParallaxNode();
}

ParallaxNodeExtras * ParallaxNodeExtras::node() {
    return new ParallaxNodeExtras();
}

void ParallaxNodeExtras::incrementOffset(Vec2 offset, Node* node) {
    for (unsigned int i = 0; i < getParallaxArray()->num; i++) {
        PointObject *point = (PointObject*)getParallaxArray()->arr[i];
        Node* curNode = point->getChild();
        if (curNode == node) {
            point->setOffset(point->getOffset() + offset);
            break;
        }
    }
}
