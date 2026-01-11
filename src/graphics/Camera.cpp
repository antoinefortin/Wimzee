#include "graphics/Camera.h"

Camera::Camera(
    float fov, float aspectRatio, float nearPlane, float farPlane 
):
// Camera default srettings
    m_Position(0.0f, 0.0f, 3.0f),
    m_Pitch(0.0f),
    m_Yaw(-90.0f), // lookin -z 
    m_WorldUp(0.0f, 1.0f, 0.0f), // Y+ for world
    m_Mode(CameraMode::Perspective), // gives perspective by default
    // these are pass from consutrcrtor args
    m_FOV(fov),
    m_AspectRatio(aspectRatio),
    m_NearPlane(nearPlane),
    m_FarPlane(farPlane)

{

    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() const 
{
    // https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml 
    return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    glm::mat4 pm{};
    if (m_Mode == CameraMode::Perspective) {
        pm = glm::perspective(glm::radians(m_FOV),
         m_AspectRatio, 
         m_NearPlane, 
         m_FarPlane);
    } else {
        pm =  glm::ortho(m_OrthoLeft, m_OrthoRight, m_OrthoBottom, m_OrthoTop, m_NearPlane, m_FarPlane);
    }
    return pm;
}


void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
}


void Camera::LookAt(const glm::vec3& target) {
    glm::vec3 direction = glm::normalize(target - m_Position);
    
    m_Pitch = glm::degrees(asin(direction.y));
    m_Yaw = glm::degrees(atan2(direction.z, direction.x));
    
    UpdateVectors();
}


void Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, 
    float farPlane)
{
    m_Mode = CameraMode::Perspective;
    m_FOV    = fov;
    m_AspectRatio = aspectRatio;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
}

void Camera::SetOrthographic(float left,
     float right, float bottom, float top, float nearPlane, float farPlane) {
    m_Mode = CameraMode::Orthographic;
    m_OrthoLeft = left;
    m_OrthoRight = right;
    m_OrthoBottom = bottom;
    m_OrthoTop = top;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
}

void Camera::SetAspectRatio(float aspectRatio) {
    m_AspectRatio = aspectRatio;
}

void Camera::SetFOV(float fov) {
    m_FOV = fov;
}

void Camera::MoveForward(float amount) {
    m_Position += m_Forward * amount;
}

void Camera::MoveRight(float amount) {
    m_Position += m_Right * amount;
}

void Camera::MoveUp(float amount) {
    m_Position += m_WorldUp * amount;
}

void Camera::Rotate(float pitchDelta, float yawDelta) {
    m_Pitch += pitchDelta;
    m_Yaw += yawDelta;
    
    if (clampRotation) {
        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;
    }
    
    UpdateVectors();
}
void Camera::UpdateVectors()
{

    // Calc forward vector
    glm::vec3 forward{};

    forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    forward.y = sin(glm::radians(m_Pitch));
    forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Forward = glm::normalize(forward);

    // Cross producxt for right and up 
    m_Right = glm::normalize(glm::cross(m_Forward, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}


Camera::~Camera()
{

}