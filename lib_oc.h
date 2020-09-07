/**
 * @file lib_oc
 * @brief Object Classification library
 *
 * Functions used to classify objects based on their shape.
 * The code uses chain code histograms and a kNN algorithm to classify objects.
 *
 * @author $Author: Catarina Silva $
 * @version $Revision: 1.0 $
 * @date $Date: 2020/01/05 $
 */

#ifndef OC_H
#define OC_H

#include "json.hpp"
#include "lib_od.h"

using json = nlohmann::json;

class Features {
  private:
    std::array<double, 8> hist;
    double circularity;
    bool convex;
    double aspect_ratio;
    double extent;
    friend std::ostream& operator<<(std::ostream&, const Features&);

  public:
    Features(const std::array<double, 8> &, const double, const bool, const double, const double);
    Features(const std::vector<cv::Point>&);
    double distance(const Features&, const unsigned int p=2) const;
    std::vector<double> get_features() const;
    std::array<double, 8> get_histogram() const;
    double get_circularity() const;
    bool get_convex() const;
    double get_aspect_ratio() const;
    double get_extent() const;
};

class KNN {
  private:
    unsigned int k, d;
    std::vector<std::pair<std::string, Features>> instances;
    friend std::ostream& operator<<(std::ostream&, const KNN&);

  public:
    KNN(const unsigned int, const unsigned int);
    KNN(const unsigned int, const unsigned int, const std::vector<std::pair<std::string, Features>>&);
    void learn(const std::vector<std::pair<std::string, Features>>&);
    std::string predict(const Object&) const;
    void store(const std::string&) const;
    static KNN load(const std::string&);
};

class LR {
  private:
    std::vector<double> parameters;
    friend std::ostream& operator<<(std::ostream&, const LR&);
  public:
    LR();
    LR(const std::vector<double> parameters);
    void learn(const std::vector<std::pair<std::string, Features>>&, const double alpha=0.01, const double beta=0.1);
    std::string predict(const Object&) const;
    void store(const std::string&) const;
    static LR load(const std::string&);
};

#endif
