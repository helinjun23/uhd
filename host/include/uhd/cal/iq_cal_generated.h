// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_IQCAL_UHD_USRP_CAL_H_
#define FLATBUFFERS_GENERATED_IQCAL_UHD_USRP_CAL_H_

#include "flatbuffers/flatbuffers.h"

#include "cal_metadata_generated.h"

namespace uhd {
namespace usrp {
namespace cal {

struct IQCalCoeff;

struct IQCalCoeffs;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(8) IQCalCoeff FLATBUFFERS_FINAL_CLASS {
 private:
  double freq_;
  double coeff_real_;
  double coeff_imag_;
  double suppression_abs_;
  double suppression_delta_;

 public:
  IQCalCoeff() {
    memset(static_cast<void *>(this), 0, sizeof(IQCalCoeff));
  }
  IQCalCoeff(double _freq, double _coeff_real, double _coeff_imag, double _suppression_abs, double _suppression_delta)
      : freq_(flatbuffers::EndianScalar(_freq)),
        coeff_real_(flatbuffers::EndianScalar(_coeff_real)),
        coeff_imag_(flatbuffers::EndianScalar(_coeff_imag)),
        suppression_abs_(flatbuffers::EndianScalar(_suppression_abs)),
        suppression_delta_(flatbuffers::EndianScalar(_suppression_delta)) {
  }
  double freq() const {
    return flatbuffers::EndianScalar(freq_);
  }
  double coeff_real() const {
    return flatbuffers::EndianScalar(coeff_real_);
  }
  double coeff_imag() const {
    return flatbuffers::EndianScalar(coeff_imag_);
  }
  double suppression_abs() const {
    return flatbuffers::EndianScalar(suppression_abs_);
  }
  double suppression_delta() const {
    return flatbuffers::EndianScalar(suppression_delta_);
  }
};
FLATBUFFERS_STRUCT_END(IQCalCoeff, 40);

struct IQCalCoeffs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_METADATA = 4,
    VT_COEFFS = 6
  };
  const Metadata *metadata() const {
    return GetPointer<const Metadata *>(VT_METADATA);
  }
  const flatbuffers::Vector<const IQCalCoeff *> *coeffs() const {
    return GetPointer<const flatbuffers::Vector<const IQCalCoeff *> *>(VT_COEFFS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_METADATA) &&
           verifier.VerifyTable(metadata()) &&
           VerifyOffset(verifier, VT_COEFFS) &&
           verifier.VerifyVector(coeffs()) &&
           verifier.EndTable();
  }
};

struct IQCalCoeffsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_metadata(flatbuffers::Offset<Metadata> metadata) {
    fbb_.AddOffset(IQCalCoeffs::VT_METADATA, metadata);
  }
  void add_coeffs(flatbuffers::Offset<flatbuffers::Vector<const IQCalCoeff *>> coeffs) {
    fbb_.AddOffset(IQCalCoeffs::VT_COEFFS, coeffs);
  }
  explicit IQCalCoeffsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  IQCalCoeffsBuilder &operator=(const IQCalCoeffsBuilder &);
  flatbuffers::Offset<IQCalCoeffs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<IQCalCoeffs>(end);
    return o;
  }
};

inline flatbuffers::Offset<IQCalCoeffs> CreateIQCalCoeffs(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Metadata> metadata = 0,
    flatbuffers::Offset<flatbuffers::Vector<const IQCalCoeff *>> coeffs = 0) {
  IQCalCoeffsBuilder builder_(_fbb);
  builder_.add_coeffs(coeffs);
  builder_.add_metadata(metadata);
  return builder_.Finish();
}

inline flatbuffers::Offset<IQCalCoeffs> CreateIQCalCoeffsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Metadata> metadata = 0,
    const std::vector<IQCalCoeff> *coeffs = nullptr) {
  auto coeffs__ = coeffs ? _fbb.CreateVectorOfStructs<IQCalCoeff>(*coeffs) : 0;
  return uhd::usrp::cal::CreateIQCalCoeffs(
      _fbb,
      metadata,
      coeffs__);
}

inline const uhd::usrp::cal::IQCalCoeffs *GetIQCalCoeffs(const void *buf) {
  return flatbuffers::GetRoot<uhd::usrp::cal::IQCalCoeffs>(buf);
}

inline const uhd::usrp::cal::IQCalCoeffs *GetSizePrefixedIQCalCoeffs(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<uhd::usrp::cal::IQCalCoeffs>(buf);
}

inline const char *IQCalCoeffsIdentifier() {
  return "IQ/f";
}

inline bool IQCalCoeffsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, IQCalCoeffsIdentifier());
}

inline bool VerifyIQCalCoeffsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<uhd::usrp::cal::IQCalCoeffs>(IQCalCoeffsIdentifier());
}

inline bool VerifySizePrefixedIQCalCoeffsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<uhd::usrp::cal::IQCalCoeffs>(IQCalCoeffsIdentifier());
}

inline void FinishIQCalCoeffsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<uhd::usrp::cal::IQCalCoeffs> root) {
  fbb.Finish(root, IQCalCoeffsIdentifier());
}

inline void FinishSizePrefixedIQCalCoeffsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<uhd::usrp::cal::IQCalCoeffs> root) {
  fbb.FinishSizePrefixed(root, IQCalCoeffsIdentifier());
}

}  // namespace cal
}  // namespace usrp
}  // namespace uhd

#endif  // FLATBUFFERS_GENERATED_IQCAL_UHD_USRP_CAL_H_