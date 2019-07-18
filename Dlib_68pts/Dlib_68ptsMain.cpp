#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <fstream>
#include "HighPerformanceTimer.hpp"

void EMPTECH_SetCurrentDirectoryToExePath()
{
    HMODULE hExe = GetModuleHandleA(NULL);
    char nameBuf[MAX_PATH] = { 0 };
    GetModuleFileNameA(hExe, nameBuf, MAX_PATH);
    std::string sName(nameBuf);
    sName = sName.substr(0, sName.rfind('\\'));
    SetCurrentDirectoryA(sName.c_str());
}

int main(int argc, char** argv)
{
    EMPTECH_SetCurrentDirectoryToExePath();
    if (argc != 3)
    {
        std::cout << "Please use this demo as blow : " << std::endl;
        std::cout << "Dlib_5ptsx.exe input_image_file_path output_txt_file_path" << std::endl;
        return 0;
    }

    try
    {
        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        dlib::shape_predictor sp;
        dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;

        std::cout << "processing image " << argv[1] << std::endl;
        dlib::array2d<dlib::rgb_pixel> img;
        dlib::load_image(img, argv[1]);
        // Make the image larger so we can detect small faces.
        //dlib::pyramid_up(img);

        std::ofstream of(argv[2], std::ofstream::app | std::ofstream::out);
        CHighPerformanceTimer* pT = new CHighPerformanceTimer("t", 2, true);
        // Now tell the face detector to give us a list of bounding boxes
        // around all the faces in the image.
        std::vector<dlib::rectangle> dets = detector(img);
        pT->Show();
        //std::cout << "Number of faces detected: " << dets.size() << std::endl;

        // Now we will go ask the shape_predictor to tell us the pose of
        // each face we detected.
        std::vector<dlib::full_object_detection> shapes;
        for (unsigned long j = 0; j < dets.size(); ++j)
        {
            dlib::full_object_detection shape = sp(img, dets[j]);

            shapes.push_back(shape);
        }
        pT->Show();
        std::cout << argv[2] << std::endl;
        of << argv[2] << "|";
        std::cout << shapes.size() << std::endl;
        for (int j = 0; j < shapes.size(); ++j)
        {
            dlib::full_object_detection& shape = shapes[j];
            std::cout << "number of parts: " << shape.num_parts() << std::endl;

            of << shape.num_parts() << "|";

            // You get the idea, you can get all the face part locations if
            // you want them.  Here we just store them in shapes so we can
            // put them on the screen.
        }
        of << pT->GetTime() << "|";
        of << std::endl;
        of.close();
        delete pT; pT = NULL;
    }
    catch (std::exception& e)
    {
        std::cout << "\nexception thrown!" << std::endl;
        std::cout << e.what() << std::endl;
    }

    return 0;
}