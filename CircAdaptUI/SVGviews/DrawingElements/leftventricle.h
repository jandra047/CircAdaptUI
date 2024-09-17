#ifndef LEFTVENTRICLE_H
#define LEFTVENTRICLE_H

#include "graphicelement.h"

class LeftVentricle : public GraphicElement
{
public:
    LeftVentricle(SVGObjectBase* parent);
private:
    QPainterPath m_path;

    QString PATCH_LV_BASAL_ANTERIOR_PATH = QString("m 317.331,202.395 c -9.386,-5.495 -20.274,-8.655 -31.841,-8.655 -11.515,0 -22.357,3.131 -31.713,8.58 0,0 -0.094,-0.124 -0.094,-0.124 0,0 -15.539,-27.05 -15.539,-27.05 0,0 -0.025,-0.106 -0.025,-0.106 13.98,-8.128 30.174,-12.797 47.371,-12.797 17.175,0 33.349,4.657 47.317,12.766 0,0 -0.085,0.168 -0.085,0.168 0,0 -15.312,27.062 -15.312,27.062 0,0 -0.079,0.156 -0.079,0.156");
    QString PATCH_LV_BASAL_POSTERIOR_PATH = QString("m 317.331,312.073 c -9.386,5.496 -20.274,8.655 -31.841,8.655 -11.515,0 -22.357,-3.131 -31.713,-8.58 0,0 -0.094,0.124 -0.094,0.124 0,0 -15.539,27.051 -15.539,27.051 0,0 -0.025,0.105 -0.025,0.105 13.98,8.129 30.174,12.797 47.371,12.797 17.175,0 33.349,-4.656 47.317,-12.765 0,0 -0.085,-0.169 -0.085,-0.169 0,0 -15.312,-27.062 -15.312,-27.062 0,0 -0.079,-0.156 -0.079,-0.156");
    QString PATCH_LV_BASAL_POSTERIOR_LATERAL_PATH = QString("m 316.811,312.372 c 9.472,-5.344 17.682,-13.163 23.504,-23.158 5.795,-9.95 8.547,-20.894 8.547,-31.722 0,0 0.155,-0.019 0.155,-0.019 0,0 31.195,0.187 31.195,0.187 0,0 0.104,0.031 0.104,0.031 -0.013,16.172 -4.128,32.515 -12.784,47.375 -8.644,14.841 -20.808,26.474 -34.845,34.463 0,0 -0.103,-0.158 -0.103,-0.158 0,0 -15.678,-26.852 -15.678,-26.852 0,0 -0.095,-0.147 -0.095,-0.147");
    QString PATCH_LV_BASAL_ANTERIOR_LATERAL_PATH = QString("m 348.889,257.401 c 0.064,-10.877 -2.646,-21.885 -8.432,-31.901 -5.759,-9.971 -13.893,-17.793 -23.291,-23.17 0,0 0.06,-0.144 0.06,-0.144 0,0 15.652,-26.985 15.652,-26.985 0,0 0.078,-0.075 0.078,-0.075 14.031,8.041 26.174,19.728 34.775,34.619 8.591,14.873 12.648,31.207 12.613,47.358 0,0 -0.188,0.011 -0.188,0.011 0,0 -31.093,0.277 -31.093,0.277 0,0 -0.174,0.01 -0.174,0.01");
    QString PATCH_LV_MID_ANTERIOR_PATH = QString("m 253.685,202.413 c 0,0 15.037,25.907 15.037,25.907 0,0 0.162,0.299 0.162,0.299 4.885,-2.849 10.548,-4.486 16.563,-4.486 6.073,0 11.787,1.669 16.705,4.569 0,0 0.033,0.023 0.033,0.023 0,0 14.797,-26.453 14.797,-26.453 0,0 -0.102,-0.114 -0.102,-0.114 -9.292,-5.349 -20.033,-8.418 -31.433,-8.418 -11.56,0 -22.442,3.156 -31.823,8.645 0,0 0.061,0.028 0.061,0.028");
    QString PATCH_LV_MID_POSTERIOR_PATH = QString("m 253.685,312.055 c 0,0 15.037,-25.906 15.037,-25.906 0,0 0.162,-0.3 0.162,-0.3 4.885,2.849 10.548,4.487 16.563,4.487 6.073,0 11.787,-1.67 16.705,-4.57 0,0 0.033,-0.023 0.033,-0.023 0,0 14.797,26.453 14.797,26.453 0,0 -0.102,0.114 -0.102,0.114 -9.292,5.349 -20.033,8.418 -31.433,8.418 -11.56,0 -22.442,-3.155 -31.823,-8.644 0,0 0.061,-0.029 0.061,-0.029");
    QString PATCH_LV_MID_POSTERIOR_LATERAL_PATH = QString("m 348.828,257.366 c 0,0 -29.954,-0.045 -29.954,-0.045 0,0 -0.341,-0.011 -0.341,-0.011 0.004,5.656 -1.432,11.373 -4.459,16.57 -3.057,5.248 -7.375,9.346 -12.356,12.136 0,0 -0.037,0.016 -0.037,0.016 0,0 15.412,26.1 15.412,26.1 0,0 0.149,-0.03 0.149,-0.03 9.3,-5.338 17.357,-13.074 23.094,-22.925 5.819,-9.99 8.569,-20.981 8.547,-31.85 0,0 -0.055,0.039 -0.055,0.039");
    QString PATCH_LV_MID_ANTERIOR_LATERAL_PATH = QString("m 317.039,202.297 c 0,0 -14.912,25.979 -14.912,25.979 0,0 -0.179,0.289 -0.179,0.289 4.912,2.806 9.162,6.891 12.17,12.099 3.038,5.259 4.451,11.042 4.399,16.751 0,0 -0.004,0.04 -0.004,0.04 0,0 30.308,-0.418 30.308,-0.418 0,0 0.048,-0.145 0.048,-0.145 -0.016,-10.723 -2.731,-21.558 -8.433,-31.429 -5.782,-10.011 -13.957,-17.855 -23.403,-23.233 0,0 0.006,0.067 0.006,0.067");
    QString PATCH_LV_APICAL_ANTERIOR_PATH = QString("m 261.965,234.09 c 0,0 23.599,23.283 23.599,23.283 0,0 23.369,-23.513 23.369,-23.513 -0.03,-0.03 -0.056,-0.056 -0.087,-0.086 -12.945,-12.772 -34.11,-12.629 -46.881,0.316");
    QString PATCH_LV_APICAL_POSTERIOR_PATH = QString("m 308.861,280.957 c 0,0 -23.297,-23.584 -23.297,-23.584 0,0 -23.311,23.57 -23.311,23.57 12.833,12.692 33.767,12.699 46.608,0.014");
    QString PATCH_LV_APICAL_LATERAL_PATH = QString("m 308.932,233.858 c 0,0 -23.368,23.515 -23.368,23.515 0,0 23.17,23.709 23.17,23.709 0.121,-0.119 0.225,-0.221 0.344,-0.341 12.818,-12.899 12.752,-34.064 -0.146,-46.883");

};

#endif // LEFTVENTRICLE_H
