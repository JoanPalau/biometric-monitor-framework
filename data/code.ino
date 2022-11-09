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
                                        if (x[2] <= 39.88602638244629) {
                                            return 0;
                                        }

                                        else {
                                            return 3;
                                        }
                                    }

                                    else {
                                        if (x[2] <= 40.058589935302734) {
                                            return 0;
                                        }

                                        else {
                                            if (x[0] <= 2.5) {
                                                if (x[3] <= 24.83981227874756) {
                                                    return 2;
                                                }

                                                else {
                                                    return 0;
                                                }
                                            }

                                            else {
                                                if (x[2] <= 90.04087448120117) {
                                                    return 2;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 90.00526428222656) {
                                        if (x[2] <= 49.87374496459961) {
                                            if (x[0] <= 1.5) {
                                                if (x[0] <= 0.5) {
                                                    return 0;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                return 0;
                                            }
                                        }

                                        else {
                                            if (x[0] <= 1.5) {
                                                if (x[0] <= 0.5) {
                                                    return 2;
                                                }

                                                else {
                                                    return 1;
                                                }
                                            }

                                            else {
                                                return 2;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[0] <= 1.5) {
                                            if (x[0] <= 0.5) {
                                                return 0;
                                            }

                                            else {
                                                return 2;
                                            }
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