// Данная флоунода при первом апдейте пишет в выходной порт true
// а затем только false. Такм образум получаем сигнал,
// который будет оправляться только один раз на старте.

#pragma once

#include "FlowNode.h"

class URHO3D_API StarterFlowNode : public FlowNode
{
    URHO3D_OBJECT(StarterFlowNode, FlowNode);

public:
    StarterFlowNode(Context* context);
    void Update(float timeStep);

    // Был ли уже отправлен сигнал.
    bool sended_ = false;
};
