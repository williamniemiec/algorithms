# K-fold Cross Validation

## Introduction

K-fold Cross Validation is a widely used resampling method. In cross validation a dataset is divided into k folds. Each fold contains 1/k cases of the full data set. A computation is performed on k-1 fold of the full dataset. The k-fold is held back and is used for testing the result. The computation is performed k times and model parameters are averaged (mean taken) over the results of the k folds. For each iteration, k-1 folds are used for training and the k-fold is used for testing.

4-fold cross validation is illustrated in the figure below. To ensure the data are randomly sampled the data is randomly shuffled at the start of the procedure. The random samples can then be efficiently sub-sampled as shown in the figure. The model is trained and tested four times. For each iteration the data is trained with three folds of the data and tested with the fold shown in the dark shading.

![image displaying 4-fold cross validation](https://github.com/MicrosoftLearning/Principles-of-Machine-Learning-Python/raw/8a26f069667d1fcd4417487beb9e138df94b948c/Module5/CrossValidation.jpg)

<hr>

## References
- [MicrosoftLearning](https://github.com/MicrosoftLearning)
- [MachineCurve](MachineCurve.com)
- Refaeilzadeh P., Tang L., Liu H. (2009) Cross-Validation. In: LIU L., ÖZSU M.T. (eds) Encyclopedia of Database Systems. Springer, Boston, MA. https://doi.org/10.1007/978-0-387-39940-9_565

