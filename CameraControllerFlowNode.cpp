#include "CameraControllerFlowNode.h"

CameraControllerFlowNode::CameraControllerFlowNode(Context* context) :
    FlowNode(context)
{
}

void CameraControllerFlowNode::Update(float timeStep)
{
    // Получаем указатель на ноду камеры из входного порта.
    Node* cameraNode = static_cast<Node*>(inputs_["CameraNode"].GetData().GetVoidPtr());
    
    // Получаем чувствительность мышки из входного порта.
    float mouseSensitivity = inputs_["MouseSensitivity"].GetData().GetFloat();

    Input* input = GetSubsystem<Input>();
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += mouseSensitivity * mouseMove.x_;
    pitch_ += mouseSensitivity * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    cameraNode->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    if (input->GetKeyDown('W'))
        cameraNode->Translate(Vector3::FORWARD * 20.0f * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode->Translate(Vector3::BACK * 20.0f * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode->Translate(Vector3::LEFT * 20.0f * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode->Translate(Vector3::RIGHT * 20.0f * timeStep);
}