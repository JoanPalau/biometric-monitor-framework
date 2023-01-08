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
                        if (x[2] >= 130.57345174357945) {
                            return 3;
                        }
                        if (x[1] <= 1.5) {
                            if (x[2] <= 92.31804275512695) {
                                if (x[2] <= 50.41830253601074) {
                                    if (x[2] <= 42.44119834899902) {
                                        return 0;
                                    }

                                    else {
                                        return 1;
                                    }
                                }

                                else {
                                    if (x[0] <= 1.5) {
                                        return 1;
                                    }

                                    else {
                                        return 2;
                                    }
                                }
                            }

                            else {
                                if (x[0] <= 1.5) {
                                    if (x[0] <= 0.5) {
                                        return 3;
                                    }

                                    else {
                                        return 2;
                                    }
                                }

                                else {
                                    return 3;
                                }
                            }
                        }

                        else {
                            return 3;
                        }
                    }

                protected:
                };
            }
        }
    }