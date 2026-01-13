#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum class CameraMode 
{
    Perspective,
    Orthographic
};

class Camera 
{
public:
    Camera(
        float fov = 45.0f, 
        float aspectRatio = 16.0f/9.0f,
        float nearPlane = 0.0f,
        float farPlane = 100.0f
    );

    // Mastrices 
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    // positijn & orientation 
    const bool clampRotation = true;
    void SetPosition(const glm::vec3& position);
    void SetRotation(float pitch, float yaw);
    void LookAt(const glm::vec3& target);

    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetForward() const { return m_Forward; }
    glm::vec3 GetRight() const { return m_Right; }
    glm::vec3 GetUp() const { return m_Up; }
    
    void MoveForward(float amount);
    void MoveRight(float amount);
    void MoveUp(float amount);
    
    void Rotate(float pitchDelta, float yawDelta);
    
    // Projection settings
    void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    void SetOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    void SetAspectRatio(float aspectRatio);
    
    float GetFOV() const { return m_FOV; }
    void SetFOV(float fov);

    ~Camera();

private:
    void UpdateVectors();
    glm::vec3 m_Position;

    float m_Pitch; // x
    float m_Yaw;    // y

    glm::vec3 m_Forward;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    glm::vec3 m_WorldUp;

    // Projection
    CameraMode m_Mode;
    float m_FOV;
    float m_AspectRatio;
    float m_NearPlane;
    float m_FarPlane;


    float m_OrthoLeft, m_OrthoRight, m_OrthoBottom, m_OrthoTop;
};
