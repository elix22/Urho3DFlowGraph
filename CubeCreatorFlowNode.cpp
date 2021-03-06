#include "CubeCreatorFlowNode.h"

CubeCreatorFlowNode::CubeCreatorFlowNode(Context* context) :
    FlowNode(context)
{
    // Создаем входные порты.
    SharedPtr<FlowInputPort> signalInputPort(new FlowInputPort(context));
    signalInputPort->node_ = this;
    inputs_["Create!"] = signalInputPort;

    SharedPtr<FlowInputPort> sceneInputPort(new FlowInputPort(context));
    sceneInputPort->node_ = this;
    inputs_["Scene"] = sceneInputPort;
}

void CubeCreatorFlowNode::Update(float timeStep)
{
    // Получаем сигнал к действию.
    bool signal = inputs_["Create!"]->ReadData().GetBool();

    if (!signal)
        return;

    // Получаем указатель на сцену из входного порта.
    Scene* scene = static_cast<Scene*>(inputs_["Scene"]->ReadData().GetVoidPtr());

    // Создаем куб в некоторой окрестности от нуля.
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* cubeNode = scene->CreateChild();
    cubeNode->SetPosition(Vector3(Random(-2.5f, 2.5f), 0.0f, Random(-2.5f, 2.5f)));
    cubeNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
    cubeNode->SetScale(1.0f);
    StaticModel* cubeObject = cubeNode->CreateComponent<StaticModel>();
    cubeObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    cubeObject->SetCastShadows(true);
}
