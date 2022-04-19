import copy
from sklearn import metrics
from sklearn.tree import DecisionTreeClassifier
import numpy as np


class CrossValidation:
    """
    Self implementation of K-Fold Cross Validation. Given a number, K, the 
    dataset is split into K partitions of approximately equal sizes. K - 1 are 
    used for training, while one is used for testing. This process is repeated
    K times, with a different partition used for testing each time. For each 
    split, the same model is trained, and performance is computed per fold. For
    evaluation purposes, the performance across all folds is returned. 
    """

    #--------------------------------------------------------------------------
    #		Methods
    #--------------------------------------------------------------------------
    def run(self, estimator, attributes: list, target: list, k: int) -> "dict[str, list]":
        """
        Performs K-Fold Cross Validation on the given data, returning the 
        performance of each fold. For this, the following metrics are returned:
        
        * Accuracy
        * Precision
        * Recall
        * F1

        :param      estimator: The object to use to fit the data.
        :param      attributes: The data to fit. Can be for example a list, or 
        an array.
        :param      target: The target variable to try to predict in the case
        of supervised learning.
        :param      k: Number of folds

        :return     Dictionary contaning the performance of each fold
        """
        generate_classifier = lambda: copy.copy(estimator)
        metrics = {
            'accuracy': [],
            'precision': [],
            'recall': [],
            'f1': []
        }

        for train_index, test_index in self.__k_fold(target, k):
            predicted_target = []
            expected_target = []
            x_train, x_test = attributes[train_index], attributes[test_index]
            y_train, y_test = target[train_index], target[test_index]

            estimator = generate_classifier()
            estimator.fit(x_train, y_train)

            predicted_target.extend(estimator.predict(x_test))
            expected_target.extend(y_test)

            metrics_current_fold = self.__evaluate(expected_target, predicted_target)
            
            for metric in metrics.keys():
                metrics[metric].append(metrics_current_fold[metric])

        return metrics

    def __k_fold(self, target: list, k: int) -> list:
        total = len(target)
        fold_size = int(total / k)
        folds = [] # Tuple list: (start_range, end_range)

        # Creates k folds
        for i in range(k-1):
            folds.append((fold_size*i, fold_size*i + fold_size))

        folds.append((fold_size*(k-1), total))

        # Generates training and testing folds
        train_test_folds = []

        for i in range(k):
            # Fold test will be i
            start_range = folds[i][0]
            end_range = folds[i][1]

            test_index = []
            for j in range(start_range, end_range):
                test_index.append(j)

            train_index = []
            for j in range(0, start_range):
                train_index.append(j)

            for j in range(end_range, total):
                train_index.append(j)

            train_test_folds.append((train_index, test_index))
        
        return train_test_folds

    def __evaluate(self, expected_target: list, predicted_target: list) -> "dict[str, list]":
        return {
            'accuracy': metrics.accuracy_score(expected_target, predicted_target),
            'precision': metrics.precision_score(expected_target, predicted_target, average='weighted'),
            'recall': metrics.recall_score(expected_target, predicted_target, average='weighted'),
            'f1': metrics.f1_score(expected_target, predicted_target, average='weighted')
        }


#------------------------------------------------------------------------------
#		Main
#------------------------------------------------------------------------------
if __name__ == '__main__':
    X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
    Y = np.array([1, 1, 1, 2, 2, 2])
    K = 5

    cross_validation = CrossValidation()
    results = cross_validation.run(DecisionTreeClassifier(), X, Y, K)

    print(results)
