#include "Init.hpp"

AngleSolver::AngleSolver(cv::String path, float scale_z)
{
    int ok = ReadCameraData(path);
    if(ok == 0)
    {
        cout<<"open xml file failed..."<<endl;
    }
    this->scale_z = scale_z;
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
    offset_x = 0.0;
    offset_y = 0.0;
    offset_z = 0.0;
}

int AngleSolver::ReadCameraData(cv::String path)
{
    cv::FileStorage fs(path,cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        cout << "read reference data failed!" << endl;
        return 0;
    }

    double fc1, fc2, cc1, cc2, k1, k2, k3, k4;
    fs["fc1"] >> fc1;
    fs["fc2"] >> fc2;
    fs["cc1"] >> cc1;
    fs["cc2"] >> cc2;
    fs["kc1"] >> k1;
    fs["kc2"] >> k2;
    fs["kc3"] >> k3;
    fs["kc4"] >> k4;

    ReferenceMatrix = (cv::Mat_<double>(3, 3) << fc1, 0, cc1, 0, fc2, cc2, 0, 0, 1);
    DistortionMatrix = (cv::Mat_<double>(5, 1) << k1, k2, 0, 0,0);

    cout << "Read Reference Matrix and Distortion Matrix success !" << endl;
    fs.release();
    return 0;
}

void AngleSolver::SetCameraPoints(Point2f *points, Point2f offset)
{
    Points_in_Camera.clear();
    for(int i=0;i<4;i++)
        Points_in_Camera.push_back(points[i] + offset);
}

void AngleSolver::SetWorldPoints(armor_race type)
{
    if (type == SMALL)
    {
        target_width = 133;
        target_height = 55;
    }
    else if (type == BIG)
    {
        target_width = 228;
        target_height = 55;
    }
    else if (type == RUNE)
    {
        target_width = 230;
        target_height = 125;
    }
    else if(type == BASE)
    {
        target_width = 400;
        target_height = 800;
    }

    Points_in_World.clear();
    float half_x = target_width / 2.0;
    float half_y = target_height / 2.0;

    Points_in_World.push_back(Point3f(-half_x, half_y, 0));
    Points_in_World.push_back(Point3f(half_x, half_y, 0));
    Points_in_World.push_back(Point3f(half_x, -half_y, 0));
    Points_in_World.push_back(Point3f(-half_x, -half_y, 0));
}

void AngleSolver::SolvePnP(int type)
{
    if(type == 0)
        cv::solvePnP(Points_in_World, Points_in_Camera, ReferenceMatrix, DistortionMatrix, rot, trans,false);
    else if(type == 1)
        cv::solvePnP(Points_in_World, Points_in_Camera, ReferenceMatrix, DistortionMatrix, rot, trans,false,SOLVEPNP_P3P);
    else if(type == 2)
        cv::solvePnP(Points_in_World, Points_in_Camera, ReferenceMatrix, DistortionMatrix, rot, trans,false,SOLVEPNP_EPNP);

    _x = trans.ptr<double>(0)[0];
    _y = trans.ptr<double>(0)[1];
    _z = trans.ptr<double>(0)[2];
}

double AngleSolver::GetTargetDistance(bool real,bool scale)
{
    distance = _z;
    if(real == true)
        distance = sqrt(_x * _x + _z * _z + _y * _y);

    if(scale == true)
        return distance * scale_z;
    else
        return distance;
}

double AngleSolver::CalculateAngle(float &angle_Yaw, float &angle_Pitch, int model)
{
    _x += offset_x;
    _y += offset_y;
    _z += offset_z;

    if(model == 1)
    {
        cv::Point3f position;
        position.x = _x;
        position.y = _y;
        position.z = _z;

        Init();
        Transform(position,angle_Pitch,angle_Yaw);

        angle_Yaw = angle_Yaw * 10;
        angle_Pitch = angle_Pitch * 10;
    }
    else
    {
        double _Yaw = atan(_x/_z) * 180 / CV_PI;
        double _Pitch = atan(_y/_z) * 180 /CV_PI;

        angle_Yaw = _Yaw;
        angle_Pitch = _Pitch;
    }
}

void AngleSolver::GetAngle(Point2f* points,float &angle_Yaw, float &angle_Pitch,armor_race type, int model,int pnp)
{
    SetCameraPoints(points);
    SetWorldPoints(type);
    SolvePnP(pnp);
    GetTargetDistance(false,false);
#if CONTROL
    Control();
#endif
    CalculateAngle(angle_Yaw,angle_Pitch,model);

//    cout<<"angle yaw"<<angle_Yaw<<endl;
//    cout<<"angle Pitch"<<angle_Pitch<<endl;
}

void AngleSolver::Control()
{
    int commend = waitKey(1);
    if(commend == 'w')
        offset_y -= 5;
    else if(commend == 's')
        offset_y += 5;
    else if(commend == 'a')
        offset_x -= 5;
    else if(commend == 'd')
        offset_x += 5;
    else if(commend == 'q')
        offset_z += 5;
    else if(commend == 'e')
        offset_z += 5;
}

AngleSolver::~AngleSolver()
{

}
