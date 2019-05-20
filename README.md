# IARC-Detection
Detection part of [IARC Mission 7](http://www.aerialroboticscompetition.org/mission7.php)

Using OpenCV’s cascade classifier

## Train XML

### Positive Samples

Because the shape of the robots is almost like a circle, so we can use HOG circle detection to get positive samples

And the robots’ appearance is pretty steady, so we can generate a bunch of positive samples by rotating and changing the intensity of a single image.

We use `opecv_createsamples.exe`  to do this job, see [here](https://docs.opencv.org/master/dc/d88/tutorial_traincascade.html) for more information

### Negative Samples

Negative samples are what not to look for, when trying to find your objects of interest. Or background.

Random cut frame and delete samples with robots by hand
We also need a negative samples description file

```powershell
dir /b > bg.txt # use this command in the nagetive smaples folder
```

### Train

According to [OpenCV‘s doc](https://docs.opencv.org/master/dc/d88/tutorial_traincascade.html) , the main hyper-parameter we can tune are:

* the number of samples
* the number of stages
* feature type: HAAR or LBP(local binary patterns)

## Experiment

Train speed: LBP > HAAR >> HOG

Positive samples / Negative samples = 1/2

Detection result: HAAR > LBP > HOG



  

  