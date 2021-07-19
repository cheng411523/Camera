#ifndef CLASSIFIER_H
#define CLASSIFIER_H

class Classifier
{
public:
    Classifier();
    void ClassInitialization();
    int SVMClassifier();
    int DNNClassifier();
    int CNNClassifier();
};

#endif
