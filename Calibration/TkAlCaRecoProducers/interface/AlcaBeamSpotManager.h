#ifndef AlcaBeamSpotManager_H
#define AlcaBeamSpotManager_H

/** \class AlcaBeamSpotManager
 *  No description available.
 *
 *  \author L. Uplegger F. Yumiceva - Fermilab
 */

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <map>
#include <string>
#include <utility>

class AlcaBeamSpotManager {
public:
  AlcaBeamSpotManager(void);
  AlcaBeamSpotManager(const edm::ParameterSet &, edm::ConsumesCollector &&);
  virtual ~AlcaBeamSpotManager(void);

  void reset(void);
  void readLumi(const edm::LuminosityBlock &);
  void createWeightedPayloads(void);
  const std::map<edm::LuminosityBlockNumber_t, std::pair<edm::Timestamp, reco::BeamSpot>> &getPayloads(void) {
    return beamSpotMap_;
  }

  typedef std::map<edm::LuminosityBlockNumber_t, std::pair<edm::Timestamp, reco::BeamSpot>>::iterator bsMap_iterator;

private:
  reco::BeamSpot weight(const bsMap_iterator &begin, const bsMap_iterator &end);
  void weight(double &mean, double &meanError, const double &val, const double &valError);
  std::pair<float, float> delta(const float &x, const float &xError, const float &nextX, const float &nextXError);
  float deltaSig(const float &num, const float &den);
  std::map<edm::LuminosityBlockNumber_t, std::pair<edm::Timestamp, reco::BeamSpot>> beamSpotMap_;

  std::string beamSpotOutputBase_;
  std::string beamSpotModuleName_;
  std::string beamSpotLabel_;
  double sigmaZCut_;
  edm::InputTag beamSpotTag_;
  edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
};

#endif
