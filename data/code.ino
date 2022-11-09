#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[2] <= 134.9273223876953) {
                            if (x[1] <= 1.5) {
                                if (x[1] <= 0.5) {
                                    if (x[0] <= 0.5) {
                                        return 3;
                                    }

                                    else {
                                        return 2;
                                    }
                                }

                                else {
                                    if (x[2] <= 90.00526428222656) {
                                        return 2;
                                    }

                                    else {
                                        return 0;
                                    }
                                }
                            }

                            else {
                                return 0;
                            }
                        }

                        else {
                            return 0;
                        }
                    }

                protected:
                };
            }
        }
    }