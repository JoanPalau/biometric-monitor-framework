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
                        if (x[1] <= 1.5) {
                            if (x[2] <= 133.42969512939453) {
                                if (x[0] <= 0.5) {
                                    if (x[1] <= 0.5) {
                                        return 3;
                                    }

                                    else {
                                        if (x[2] <= 92.04528427124023) {
                                            return 2;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 1.5) {
                                        if (x[2] <= 91.44598770141602) {
                                            return 1;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }

                                    else {
                                        if (x[2] <= 91.06436538696289) {
                                            return 2;
                                        }

                                        else {
                                            return 0;
                                        }
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