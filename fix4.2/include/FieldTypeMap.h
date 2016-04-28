#ifndef EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H
#define EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H


#include "Common.h"
#include <memory>
#include <map>

__FIX42_BEGIN

class FieldTypeMap {
public:
    static constexpr kFieldType get(Tag tag) { return map__[tag]; }

    static constexpr kFieldType get(kFieldName name) { return map__[Tag(name)]; };

private:
    FieldTypeMap() { }

    static constexpr kFieldType map__[] = {
            kFieldType::kUnknown,    /*    0    */
            kFieldType::kString,    /*    1  kFieldName::kAccount    */
            kFieldType::kString,    /*    2  kFieldName::kAdvId    */
            kFieldType::kString,    /*    3  kFieldName::kAdvRefID    */
            kFieldType::kChar,    /*    4  kFieldName::kAdvSide    */
            kFieldType::kString,    /*    5  kFieldName::kAdvTransType    */
            kFieldType::kPrice,    /*    6  kFieldName::kAvgPx    */
            kFieldType::kInt,    /*    7  kFieldName::kBeginSeqNo    */
            kFieldType::kString,    /*    8  kFieldName::kBeginString    */
            kFieldType::kInt,    /*    9  kFieldName::kBodyLength    */
            kFieldType::kString,    /*    10  kFieldName::kCheckSum    */
            kFieldType::kString,    /*    11  kFieldName::kClOrdID    */
            kFieldType::kAmt,    /*    12  kFieldName::kCommission    */
            kFieldType::kChar,    /*    13  kFieldName::kCommType    */
            kFieldType::kQty,    /*    14  kFieldName::kCumQty    */
            kFieldType::kCurrency,    /*    15  kFieldName::kCurrency    */
            kFieldType::kInt,    /*    16  kFieldName::kEndSeqNo    */
            kFieldType::kString,    /*    17  kFieldName::kExecID    */
            kFieldType::kMultipleValueString,    /*    18  kFieldName::kExecInst    */
            kFieldType::kString,    /*    19  kFieldName::kExecRefID    */
            kFieldType::kChar,    /*    20  kFieldName::kExecTransType    */
            kFieldType::kChar,    /*    21  kFieldName::kHandlInst    */
            kFieldType::kString,    /*    22  kFieldName::kIDSource    */
            kFieldType::kString,    /*    23  kFieldName::kIOIid    */
            kFieldType::kChar,    /*    24  kFieldName::kIOIOthSvc    */
            kFieldType::kChar,    /*    25  kFieldName::kIOIQltyInd    */
            kFieldType::kString,    /*    26  kFieldName::kIOIRefID    */
            kFieldType::kString,    /*    27  kFieldName::kIOIShares    */
            kFieldType::kChar,    /*    28  kFieldName::kIOITransType    */
            kFieldType::kChar,    /*    29  kFieldName::kLastCapacity    */
            kFieldType::kExchange,    /*    30  kFieldName::kLastMkt    */
            kFieldType::kPrice,    /*    31  kFieldName::kLastPx    */
            kFieldType::kQty,    /*    32  kFieldName::kLastShares    */
            kFieldType::kInt,    /*    33  kFieldName::kLinesOfText    */
            kFieldType::kInt,    /*    34  kFieldName::kMsgSeqNum    */
            kFieldType::kString,    /*    35  kFieldName::kMsgType    */
            kFieldType::kInt,    /*    36  kFieldName::kNewSeqNo    */
            kFieldType::kString,    /*    37  kFieldName::kOrderID    */
            kFieldType::kQty,    /*    38  kFieldName::kOrderQty    */
            kFieldType::kChar,    /*    39  kFieldName::kOrdStatus    */
            kFieldType::kChar,    /*    40  kFieldName::kOrdType    */
            kFieldType::kString,    /*    41  kFieldName::kOrigClOrdID    */
            kFieldType::kUTCTimestamp,    /*    42  kFieldName::kOrigTime    */
            kFieldType::kBoolean,    /*    43  kFieldName::kPossDupFlag    */
            kFieldType::kPrice,    /*    44  kFieldName::kPrice    */
            kFieldType::kInt,    /*    45  kFieldName::kRefSeqNum    */
            kFieldType::kString,    /*    46  kFieldName::kRelatdSym    */
            kFieldType::kChar,    /*    47  kFieldName::kRule80A    */
            kFieldType::kString,    /*    48  kFieldName::kSecurityID    */
            kFieldType::kString,    /*    49  kFieldName::kSenderCompID    */
            kFieldType::kString,    /*    50  kFieldName::kSenderSubID    */
            kFieldType::kLocalMktDate,    /*    51  kFieldName::kSendingDate    */
            kFieldType::kUTCTimestamp,    /*    52  kFieldName::kSendingTime    */
            kFieldType::kQty,    /*    53  kFieldName::kShares    */
            kFieldType::kChar,    /*    54  kFieldName::kSide    */
            kFieldType::kString,    /*    55  kFieldName::kSymbol    */
            kFieldType::kString,    /*    56  kFieldName::kTargetCompID    */
            kFieldType::kString,    /*    57  kFieldName::kTargetSubID    */
            kFieldType::kString,    /*    58  kFieldName::kText    */
            kFieldType::kChar,    /*    59  kFieldName::kTimeInForce    */
            kFieldType::kUTCTimestamp,    /*    60  kFieldName::kTransactTime    */
            kFieldType::kChar,    /*    61  kFieldName::kUrgency    */
            kFieldType::kUTCTimestamp,    /*    62  kFieldName::kValidUntilTime    */
            kFieldType::kChar,    /*    63  kFieldName::kSettlmntTyp    */
            kFieldType::kLocalMktDate,    /*    64  kFieldName::kFutSettDate    */
            kFieldType::kString,    /*    65  kFieldName::kSymbolSfx    */
            kFieldType::kString,    /*    66  kFieldName::kListID    */
            kFieldType::kInt,    /*    67  kFieldName::kListSeqNo    */
            kFieldType::kInt,    /*    68  kFieldName::kTotNoOrders    */
            kFieldType::kString,    /*    69  kFieldName::kListExecInst    */
            kFieldType::kString,    /*    70  kFieldName::kAllocID    */
            kFieldType::kChar,    /*    71  kFieldName::kAllocTransType    */
            kFieldType::kString,    /*    72  kFieldName::kRefAllocID    */
            kFieldType::kRepeatGroup,    /*    73  kFieldName::kNoOrders    */
            kFieldType::kInt,    /*    74  kFieldName::kAvgPrxPrecision    */
            kFieldType::kLocalMktDate,    /*    75  kFieldName::kTradeDate    */
            kFieldType::kString,    /*    76  kFieldName::kExecBroker    */
            kFieldType::kChar,    /*    77  kFieldName::kOpenClose    */
            kFieldType::kRepeatGroup,    /*    78  kFieldName::kNoAllocs    */
            kFieldType::kString,    /*    79  kFieldName::kAllocAccount    */
            kFieldType::kQty,    /*    80  kFieldName::kAllocShares    */
            kFieldType::kChar,    /*    81  kFieldName::kProcessCode    */
            kFieldType::kRepeatGroup,    /*    82  kFieldName::kNoRpts    */
            kFieldType::kInt,    /*    83  kFieldName::kRptSeq    */
            kFieldType::kQty,    /*    84  kFieldName::kCxlQty    */
            kFieldType::kRepeatGroup,    /*    85  kFieldName::kNoDlvyInst    */
            kFieldType::kString,    /*    86  kFieldName::kDlvyInst    */
            kFieldType::kInt,    /*    87  kFieldName::kAllocStatus    */
            kFieldType::kInt,    /*    88  kFieldName::kAllocRejCode    */
            kFieldType::kData,    /*    89  kFieldName::kSignature    */
            kFieldType::kLength,    /*    90  kFieldName::kSecureDataLen    */
            kFieldType::kData,    /*    91  kFieldName::kSecureData    */
            kFieldType::kString,    /*    92  kFieldName::kBrokerOfCredit    */
            kFieldType::kLength,    /*    93  kFieldName::kSignatureLength    */
            kFieldType::kChar,    /*    94  kFieldName::kEmailType    */
            kFieldType::kLength,    /*    95  kFieldName::kRawDataLength    */
            kFieldType::kData,    /*    96  kFieldName::kRawData    */
            kFieldType::kBoolean,    /*    97  kFieldName::kPossResend    */
            kFieldType::kInt,    /*    98  kFieldName::kEncryptMethod    */
            kFieldType::kPrice,    /*    99  kFieldName::kStopPx    */
            kFieldType::kExchange,    /*    100  kFieldName::kExDestination    */
            kFieldType::kUnknown,    /*    101    */
            kFieldType::kInt,    /*    102  kFieldName::kCxlRejReason    */
            kFieldType::kInt,    /*    103  kFieldName::kOrdRejReason    */
            kFieldType::kChar,    /*    104  kFieldName::kIOIQualifier    */
            kFieldType::kString,    /*    105  kFieldName::kWaveNo    */
            kFieldType::kString,    /*    106  kFieldName::kIssuer    */
            kFieldType::kString,    /*    107  kFieldName::kSecurityDesc    */
            kFieldType::kInt,    /*    108  kFieldName::kHeartBtInt    */
            kFieldType::kString,    /*    109  kFieldName::kClientID    */
            kFieldType::kQty,    /*    110  kFieldName::kMinQty    */
            kFieldType::kQty,    /*    111  kFieldName::kMaxFloor    */
            kFieldType::kString,    /*    112  kFieldName::kTestReqID    */
            kFieldType::kBoolean,    /*    113  kFieldName::kReportToExch    */
            kFieldType::kBoolean,    /*    114  kFieldName::kLocateReqd    */
            kFieldType::kString,    /*    115  kFieldName::kOnBehalfOfCompID    */
            kFieldType::kString,    /*    116  kFieldName::kOnBehalfOfSubID    */
            kFieldType::kString,    /*    117  kFieldName::kQuoteID    */
            kFieldType::kAmt,    /*    118  kFieldName::kNetMoney    */
            kFieldType::kAmt,    /*    119  kFieldName::kSettlCurrAmt    */
            kFieldType::kCurrency,    /*    120  kFieldName::kSettlCurrency    */
            kFieldType::kBoolean,    /*    121  kFieldName::kForexReq    */
            kFieldType::kUTCTimestamp,    /*    122  kFieldName::kOrigSendingTime    */
            kFieldType::kBoolean,    /*    123  kFieldName::kGapFillFlag    */
            kFieldType::kRepeatGroup,    /*    124  kFieldName::kNoExecs    */
            kFieldType::kChar,    /*    125  kFieldName::kCxlType    */
            kFieldType::kUTCTimestamp,    /*    126  kFieldName::kExpireTime    */
            kFieldType::kChar,    /*    127  kFieldName::kDKReason    */
            kFieldType::kString,    /*    128  kFieldName::kDeliverToCompID    */
            kFieldType::kString,    /*    129  kFieldName::kDeliverToSubID    */
            kFieldType::kBoolean,    /*    130  kFieldName::kIOINaturalFlag    */
            kFieldType::kString,    /*    131  kFieldName::kQuoteReqID    */
            kFieldType::kPrice,    /*    132  kFieldName::kBidPx    */
            kFieldType::kPrice,    /*    133  kFieldName::kOfferPx    */
            kFieldType::kQty,    /*    134  kFieldName::kBidSize    */
            kFieldType::kQty,    /*    135  kFieldName::kOfferSize    */
            kFieldType::kRepeatGroup,    /*    136  kFieldName::kNoMiscFees    */
            kFieldType::kAmt,    /*    137  kFieldName::kMiscFeeAmt    */
            kFieldType::kCurrency,    /*    138  kFieldName::kMiscFeeCurr    */
            kFieldType::kChar,    /*    139  kFieldName::kMiscFeeType    */
            kFieldType::kPrice,    /*    140  kFieldName::kPrevClosePx    */
            kFieldType::kBoolean,    /*    141  kFieldName::kResetSeqNumFlag    */
            kFieldType::kString,    /*    142  kFieldName::kSenderLocationID    */
            kFieldType::kString,    /*    143  kFieldName::kTargetLocationID    */
            kFieldType::kString,    /*    144  kFieldName::kOnBehalfOfLocationID    */
            kFieldType::kString,    /*    145  kFieldName::kDeliverToLocationID    */
            kFieldType::kRepeatGroup,    /*    146  kFieldName::kNoRelatedSym    */
            kFieldType::kString,    /*    147  kFieldName::kSubject    */
            kFieldType::kString,    /*    148  kFieldName::kHeadline    */
            kFieldType::kString,    /*    149  kFieldName::kURLLink    */
            kFieldType::kChar,    /*    150  kFieldName::kExecType    */
            kFieldType::kQty,    /*    151  kFieldName::kLeavesQty    */
            kFieldType::kQty,    /*    152  kFieldName::kCashOrderQty    */
            kFieldType::kPrice,    /*    153  kFieldName::kAllocAvgPx    */
            kFieldType::kAmt,    /*    154  kFieldName::kAllocNetMoney    */
            kFieldType::kFloat,    /*    155  kFieldName::kSettlCurrFxRate    */
            kFieldType::kChar,    /*    156  kFieldName::kSettlCurrFxRateCalc    */
            kFieldType::kInt,    /*    157  kFieldName::kNumDaysInterest    */
            kFieldType::kFloat,    /*    158  kFieldName::kAccruedInterestRate    */
            kFieldType::kAmt,    /*    159  kFieldName::kAccruedInterestAmt    */
            kFieldType::kChar,    /*    160  kFieldName::kSettlInstMode    */
            kFieldType::kString,    /*    161  kFieldName::kAllocText    */
            kFieldType::kString,    /*    162  kFieldName::kSettlInstID    */
            kFieldType::kChar,    /*    163  kFieldName::kSettlInstTransType    */
            kFieldType::kString,    /*    164  kFieldName::kEmailThreadID    */
            kFieldType::kChar,    /*    165  kFieldName::kSettlInstSource    */
            kFieldType::kString,    /*    166  kFieldName::kSettlLocation    */
            kFieldType::kString,    /*    167  kFieldName::kSecurityType    */
            kFieldType::kUTCTimestamp,    /*    168  kFieldName::kEffectiveTime    */
            kFieldType::kInt,    /*    169  kFieldName::kStandInstDbType    */
            kFieldType::kString,    /*    170  kFieldName::kStandInstDbName    */
            kFieldType::kString,    /*    171  kFieldName::kStandInstDbID    */
            kFieldType::kInt,    /*    172  kFieldName::kSettlDeliveryType    */
            kFieldType::kString,    /*    173  kFieldName::kSettlDepositoryCode    */
            kFieldType::kString,    /*    174  kFieldName::kSettlBrkrCode    */
            kFieldType::kString,    /*    175  kFieldName::kSettlInstCode    */
            kFieldType::kString,    /*    176  kFieldName::kSecuritySettlAgentName    */
            kFieldType::kString,    /*    177  kFieldName::kSecuritySettlAgentCode    */
            kFieldType::kString,    /*    178  kFieldName::kSecuritySettlAgentAcctNum    */
            kFieldType::kString,    /*    179  kFieldName::kSecuritySettlAgentAcctName    */
            kFieldType::kString,    /*    180  kFieldName::kSecuritySettlAgentContactName    */
            kFieldType::kString,    /*    181  kFieldName::kSecuritySettlAgentContactPhone    */
            kFieldType::kString,    /*    182  kFieldName::kCashSettlAgentName    */
            kFieldType::kString,    /*    183  kFieldName::kCashSettlAgentCode    */
            kFieldType::kString,    /*    184  kFieldName::kCashSettlAgentAcctNum    */
            kFieldType::kString,    /*    185  kFieldName::kCashSettlAgentAcctName    */
            kFieldType::kString,    /*    186  kFieldName::kCashSettlAgentContactName    */
            kFieldType::kString,    /*    187  kFieldName::kCashSettlAgentContactPhone    */
            kFieldType::kPrice,    /*    188  kFieldName::kBidSpotRate    */
            kFieldType::kPriceOffset,    /*    189  kFieldName::kBidForwardPoints    */
            kFieldType::kPrice,    /*    190  kFieldName::kOfferSpotRate    */
            kFieldType::kPriceOffset,    /*    191  kFieldName::kOfferForwardPoints    */
            kFieldType::kQty,    /*    192  kFieldName::kOrderQty2    */
            kFieldType::kLocalMktDate,    /*    193  kFieldName::kFutSettDate2    */
            kFieldType::kPrice,    /*    194  kFieldName::kLastSpotRate    */
            kFieldType::kPriceOffset,    /*    195  kFieldName::kLastForwardPoints    */
            kFieldType::kString,    /*    196  kFieldName::kAllocLinkID    */
            kFieldType::kInt,    /*    197  kFieldName::kAllocLinkType    */
            kFieldType::kString,    /*    198  kFieldName::kSecondaryOrderID    */
            kFieldType::kRepeatGroup,    /*    199  kFieldName::kNoIOIQualifiers    */
            kFieldType::kMonthYear,    /*    200  kFieldName::kMaturityMonthYear    */
            kFieldType::kInt,    /*    201  kFieldName::kPutOrCall    */
            kFieldType::kPrice,    /*    202  kFieldName::kStrikePrice    */
            kFieldType::kInt,    /*    203  kFieldName::kCoveredOrUncovered    */
            kFieldType::kInt,    /*    204  kFieldName::kCustomerOrFirm    */
            kFieldType::kDayOfMonth,    /*    205  kFieldName::kMaturityDay    */
            kFieldType::kChar,    /*    206  kFieldName::kOptAttribute    */
            kFieldType::kExchange,    /*    207  kFieldName::kSecurityExchange    */
            kFieldType::kBoolean,    /*    208  kFieldName::kNotifyBrokerOfCredit    */
            kFieldType::kInt,    /*    209  kFieldName::kAllocHandlInst    */
            kFieldType::kQty,    /*    210  kFieldName::kMaxShow    */
            kFieldType::kPriceOffset,    /*    211  kFieldName::kPegDifference    */
            kFieldType::kLength,    /*    212  kFieldName::kXmlDataLen    */
            kFieldType::kData,    /*    213  kFieldName::kXmlData    */
            kFieldType::kString,    /*    214  kFieldName::kSettlInstRefID    */
            kFieldType::kRepeatGroup,    /*    215  kFieldName::kNoRoutingIDs    */
            kFieldType::kInt,    /*    216  kFieldName::kRoutingType    */
            kFieldType::kString,    /*    217  kFieldName::kRoutingID    */
            kFieldType::kPriceOffset,    /*    218  kFieldName::kSpreadToBenchmark    */
            kFieldType::kChar,    /*    219  kFieldName::kBenchmark    */
            kFieldType::kUnknown,    /*    220    */
            kFieldType::kUnknown,    /*    221    */
            kFieldType::kUnknown,    /*    222    */
            kFieldType::kFloat,    /*    223  kFieldName::kCouponRate    */
            kFieldType::kUnknown,    /*    224    */
            kFieldType::kUnknown,    /*    225    */
            kFieldType::kUnknown,    /*    226    */
            kFieldType::kUnknown,    /*    227    */
            kFieldType::kUnknown,    /*    228    */
            kFieldType::kUnknown,    /*    229    */
            kFieldType::kUnknown,    /*    230    */
            kFieldType::kFloat,    /*    231  kFieldName::kContractMultiplier    */
            kFieldType::kUnknown,    /*    232    */
            kFieldType::kUnknown,    /*    233    */
            kFieldType::kUnknown,    /*    234    */
            kFieldType::kUnknown,    /*    235    */
            kFieldType::kUnknown,    /*    236    */
            kFieldType::kUnknown,    /*    237    */
            kFieldType::kUnknown,    /*    238    */
            kFieldType::kUnknown,    /*    239    */
            kFieldType::kUnknown,    /*    240    */
            kFieldType::kUnknown,    /*    241    */
            kFieldType::kUnknown,    /*    242    */
            kFieldType::kUnknown,    /*    243    */
            kFieldType::kUnknown,    /*    244    */
            kFieldType::kUnknown,    /*    245    */
            kFieldType::kUnknown,    /*    246    */
            kFieldType::kUnknown,    /*    247    */
            kFieldType::kUnknown,    /*    248    */
            kFieldType::kUnknown,    /*    249    */
            kFieldType::kUnknown,    /*    250    */
            kFieldType::kUnknown,    /*    251    */
            kFieldType::kUnknown,    /*    252    */
            kFieldType::kUnknown,    /*    253    */
            kFieldType::kUnknown,    /*    254    */
            kFieldType::kUnknown,    /*    255    */
            kFieldType::kUnknown,    /*    256    */
            kFieldType::kUnknown,    /*    257    */
            kFieldType::kUnknown,    /*    258    */
            kFieldType::kUnknown,    /*    259    */
            kFieldType::kUnknown,    /*    260    */
            kFieldType::kUnknown,    /*    261    */
            kFieldType::kString,    /*    262  kFieldName::kMDReqID    */
            kFieldType::kChar,    /*    263  kFieldName::kSubscriptionRequestType    */
            kFieldType::kInt,    /*    264  kFieldName::kMarketDepth    */
            kFieldType::kInt,    /*    265  kFieldName::kMDUpdateType    */
            kFieldType::kBoolean,    /*    266  kFieldName::kAggregatedBook    */
            kFieldType::kRepeatGroup,    /*    267  kFieldName::kNoMDEntryTypes    */
            kFieldType::kRepeatGroup,    /*    268  kFieldName::kNoMDEntries    */
            kFieldType::kChar,    /*    269  kFieldName::kMDEntryType    */
            kFieldType::kPrice,    /*    270  kFieldName::kMDEntryPx    */
            kFieldType::kQty,    /*    271  kFieldName::kMDEntrySize    */
            kFieldType::kUTCDate,    /*    272  kFieldName::kMDEntryDate    */
            kFieldType::kUTCTimeOnly,    /*    273  kFieldName::kMDEntryTime    */
            kFieldType::kChar,    /*    274  kFieldName::kTickDirection    */
            kFieldType::kExchange,    /*    275  kFieldName::kMDMkt    */
            kFieldType::kMultipleValueString,    /*    276  kFieldName::kQuoteCondition    */
            kFieldType::kMultipleValueString,    /*    277  kFieldName::kTradeCondition    */
            kFieldType::kString,    /*    278  kFieldName::kMDEntryID    */
            kFieldType::kChar,    /*    279  kFieldName::kMDUpdateAction    */
            kFieldType::kString,    /*    280  kFieldName::kMDEntryRefID    */
            kFieldType::kChar,    /*    281  kFieldName::kMDReqRejReason    */
            kFieldType::kString,    /*    282  kFieldName::kMDEntryOriginator    */
            kFieldType::kString,    /*    283  kFieldName::kLocationID    */
            kFieldType::kString,    /*    284  kFieldName::kDeskID    */
            kFieldType::kChar,    /*    285  kFieldName::kDeleteReason    */
            kFieldType::kChar,    /*    286  kFieldName::kOpenCloseSettleFlag    */
            kFieldType::kInt,    /*    287  kFieldName::kSellerDays    */
            kFieldType::kString,    /*    288  kFieldName::kMDEntryBuyer    */
            kFieldType::kString,    /*    289  kFieldName::kMDEntrySeller    */
            kFieldType::kInt,    /*    290  kFieldName::kMDEntryPositionNo    */
            kFieldType::kChar,    /*    291  kFieldName::kFinancialStatus    */
            kFieldType::kChar,    /*    292  kFieldName::kCorporateAction    */
            kFieldType::kQty,    /*    293  kFieldName::kDefBidSize    */
            kFieldType::kQty,    /*    294  kFieldName::kDefOfferSize    */
            kFieldType::kRepeatGroup,    /*    295  kFieldName::kNoQuoteEntries    */
            kFieldType::kRepeatGroup,    /*    296  kFieldName::kNoQuoteSets    */
            kFieldType::kInt,    /*    297  kFieldName::kQuoteAckStatus    */
            kFieldType::kInt,    /*    298  kFieldName::kQuoteCancelType    */
            kFieldType::kString,    /*    299  kFieldName::kQuoteEntryID    */
            kFieldType::kInt,    /*    300  kFieldName::kQuoteRejectReason    */
            kFieldType::kInt,    /*    301  kFieldName::kQuoteResponseLevel    */
            kFieldType::kString,    /*    302  kFieldName::kQuoteSetID    */
            kFieldType::kInt,    /*    303  kFieldName::kQuoteRequestType    */
            kFieldType::kInt,    /*    304  kFieldName::kTotQuoteEntries    */
            kFieldType::kString,    /*    305  kFieldName::kUnderlyingIDSource    */
            kFieldType::kString,    /*    306  kFieldName::kUnderlyingIssuer    */
            kFieldType::kString,    /*    307  kFieldName::kUnderlyingSecurityDesc    */
            kFieldType::kExchange,    /*    308  kFieldName::kUnderlyingSecurityExchange    */
            kFieldType::kString,    /*    309  kFieldName::kUnderlyingSecurityID    */
            kFieldType::kString,    /*    310  kFieldName::kUnderlyingSecurityType    */
            kFieldType::kString,    /*    311  kFieldName::kUnderlyingSymbol    */
            kFieldType::kString,    /*    312  kFieldName::kUnderlyingSymbolSfx    */
            kFieldType::kMonthYear,    /*    313  kFieldName::kUnderlyingMaturityMonthYear    */
            kFieldType::kDayOfMonth,    /*    314  kFieldName::kUnderlyingMaturityDay    */
            kFieldType::kInt,    /*    315  kFieldName::kUnderlyingPutOrCall    */
            kFieldType::kPrice,    /*    316  kFieldName::kUnderlyingStrikePrice    */
            kFieldType::kChar,    /*    317  kFieldName::kUnderlyingOptAttribute    */
            kFieldType::kCurrency,    /*    318  kFieldName::kUnderlyingCurrency    */
            kFieldType::kQty,    /*    319  kFieldName::kRatioQty    */
            kFieldType::kString,    /*    320  kFieldName::kSecurityReqID    */
            kFieldType::kInt,    /*    321  kFieldName::kSecurityRequestType    */
            kFieldType::kString,    /*    322  kFieldName::kSecurityResponseID    */
            kFieldType::kInt,    /*    323  kFieldName::kSecurityResponseType    */
            kFieldType::kString,    /*    324  kFieldName::kSecurityStatusReqID    */
            kFieldType::kBoolean,    /*    325  kFieldName::kUnsolicitedIndicator    */
            kFieldType::kInt,    /*    326  kFieldName::kSecurityTradingStatus    */
            kFieldType::kChar,    /*    327  kFieldName::kHaltReasonChar    */
            kFieldType::kBoolean,    /*    328  kFieldName::kInViewOfCommon    */
            kFieldType::kBoolean,    /*    329  kFieldName::kDueToRelated    */
            kFieldType::kQty,    /*    330  kFieldName::kBuyVolume    */
            kFieldType::kQty,    /*    331  kFieldName::kSellVolume    */
            kFieldType::kPrice,    /*    332  kFieldName::kHighPx    */
            kFieldType::kPrice,    /*    333  kFieldName::kLowPx    */
            kFieldType::kInt,    /*    334  kFieldName::kAdjustment    */
            kFieldType::kString,    /*    335  kFieldName::kTradSesReqID    */
            kFieldType::kString,    /*    336  kFieldName::kTradingSessionID    */
            kFieldType::kString,    /*    337  kFieldName::kContraTrader    */
            kFieldType::kInt,    /*    338  kFieldName::kTradSesMethod    */
            kFieldType::kInt,    /*    339  kFieldName::kTradSesMode    */
            kFieldType::kInt,    /*    340  kFieldName::kTradSesStatus    */
            kFieldType::kUTCTimestamp,    /*    341  kFieldName::kTradSesStartTime    */
            kFieldType::kUTCTimestamp,    /*    342  kFieldName::kTradSesOpenTime    */
            kFieldType::kUTCTimestamp,    /*    343  kFieldName::kTradSesPreCloseTime    */
            kFieldType::kUTCTimestamp,    /*    344  kFieldName::kTradSesCloseTime    */
            kFieldType::kUTCTimestamp,    /*    345  kFieldName::kTradSesEndTime    */
            kFieldType::kInt,    /*    346  kFieldName::kNumberOfOrders    */
            kFieldType::kString,    /*    347  kFieldName::kMessageEncoding    */
            kFieldType::kLength,    /*    348  kFieldName::kEncodedIssuerLen    */
            kFieldType::kData,    /*    349  kFieldName::kEncodedIssuer    */
            kFieldType::kLength,    /*    350  kFieldName::kEncodedSecurityDescLen    */
            kFieldType::kData,    /*    351  kFieldName::kEncodedSecurityDesc    */
            kFieldType::kLength,    /*    352  kFieldName::kEncodedListExecInstLen    */
            kFieldType::kData,    /*    353  kFieldName::kEncodedListExecInst    */
            kFieldType::kLength,    /*    354  kFieldName::kEncodedTextLen    */
            kFieldType::kData,    /*    355  kFieldName::kEncodedText    */
            kFieldType::kLength,    /*    356  kFieldName::kEncodedSubjectLen    */
            kFieldType::kData,    /*    357  kFieldName::kEncodedSubject    */
            kFieldType::kLength,    /*    358  kFieldName::kEncodedHeadlineLen    */
            kFieldType::kData,    /*    359  kFieldName::kEncodedHeadline    */
            kFieldType::kLength,    /*    360  kFieldName::kEncodedAllocTextLen    */
            kFieldType::kData,    /*    361  kFieldName::kEncodedAllocText    */
            kFieldType::kLength,    /*    362  kFieldName::kEncodedUnderlyingIssuerLen    */
            kFieldType::kData,    /*    363  kFieldName::kEncodedUnderlyingIssuer    */
            kFieldType::kLength,    /*    364  kFieldName::kEncodedUnderlyingSecurityDescLen    */
            kFieldType::kData,    /*    365  kFieldName::kEncodedUnderlyingSecurityDesc    */
            kFieldType::kPrice,    /*    366  kFieldName::kAllocPrice    */
            kFieldType::kUTCTimestamp,    /*    367  kFieldName::kQuoteSetValidUntilTime    */
            kFieldType::kInt,    /*    368  kFieldName::kQuoteEntryRejectReason    */
            kFieldType::kInt,    /*    369  kFieldName::kLastMsgSeqNumProcessed    */
            kFieldType::kUTCTimestamp,    /*    370  kFieldName::kOnBehalfOfSendingTime    */
            kFieldType::kInt,    /*    371  kFieldName::kRefTagID    */
            kFieldType::kString,    /*    372  kFieldName::kRefMsgType    */
            kFieldType::kInt,    /*    373  kFieldName::kSessionRejectReason    */
            kFieldType::kChar,    /*    374  kFieldName::kBidRequestTransType    */
            kFieldType::kString,    /*    375  kFieldName::kContraBroker    */
            kFieldType::kString,    /*    376  kFieldName::kComplianceID    */
            kFieldType::kBoolean,    /*    377  kFieldName::kSolicitedFlag    */
            kFieldType::kInt,    /*    378  kFieldName::kExecRestatementReason    */
            kFieldType::kString,    /*    379  kFieldName::kBusinessRejectRefID    */
            kFieldType::kInt,    /*    380  kFieldName::kBusinessRejectReason    */
            kFieldType::kAmt,    /*    381  kFieldName::kGrossTradeAmt    */
            kFieldType::kRepeatGroup,    /*    382  kFieldName::kNoContraBrokers    */
            kFieldType::kInt,    /*    383  kFieldName::kMaxMessageSize    */
            kFieldType::kRepeatGroup,    /*    384  kFieldName::kNoMsgTypes    */
            kFieldType::kChar,    /*    385  kFieldName::kMsgDirection    */
            kFieldType::kRepeatGroup,    /*    386  kFieldName::kNoTradingSessions    */
            kFieldType::kQty,    /*    387  kFieldName::kTotalVolumeTraded    */
            kFieldType::kChar,    /*    388  kFieldName::kDiscretionInst    */
            kFieldType::kPriceOffset,    /*    389  kFieldName::kDiscretionOffset    */
            kFieldType::kString,    /*    390  kFieldName::kBidID    */
            kFieldType::kString,    /*    391  kFieldName::kClientBidID    */
            kFieldType::kString,    /*    392  kFieldName::kListName    */
            kFieldType::kInt,    /*    393  kFieldName::kTotalNumSecurities    */
            kFieldType::kInt,    /*    394  kFieldName::kBidType    */
            kFieldType::kInt,    /*    395  kFieldName::kNumTickets    */
            kFieldType::kAmt,    /*    396  kFieldName::kSideValue1    */
            kFieldType::kAmt,    /*    397  kFieldName::kSideValue2    */
            kFieldType::kRepeatGroup,    /*    398  kFieldName::kNoBidDescriptors    */
            kFieldType::kInt,    /*    399  kFieldName::kBidDescriptorType    */
            kFieldType::kString,    /*    400  kFieldName::kBidDescriptor    */
            kFieldType::kInt,    /*    401  kFieldName::kSideValueInd    */
            kFieldType::kFloat,    /*    402  kFieldName::kLiquidityPctLow    */
            kFieldType::kFloat,    /*    403  kFieldName::kLiquidityPctHigh    */
            kFieldType::kAmt,    /*    404  kFieldName::kLiquidityValue    */
            kFieldType::kFloat,    /*    405  kFieldName::kEFPTrackingError    */
            kFieldType::kAmt,    /*    406  kFieldName::kFairValue    */
            kFieldType::kFloat,    /*    407  kFieldName::kOutsideIndexPct    */
            kFieldType::kAmt,    /*    408  kFieldName::kValueOfFutures    */
            kFieldType::kInt,    /*    409  kFieldName::kLiquidityIndType    */
            kFieldType::kFloat,    /*    410  kFieldName::kWtAverageLiquidity    */
            kFieldType::kBoolean,    /*    411  kFieldName::kExchangeForPhysical    */
            kFieldType::kAmt,    /*    412  kFieldName::kOutMainCntryUIndex    */
            kFieldType::kFloat,    /*    413  kFieldName::kCrossPercent    */
            kFieldType::kInt,    /*    414  kFieldName::kProgRptReqs    */
            kFieldType::kInt,    /*    415  kFieldName::kProgPeriodInterval    */
            kFieldType::kInt,    /*    416  kFieldName::kIncTaxInd    */
            kFieldType::kInt,    /*    417  kFieldName::kNumBidders    */
            kFieldType::kChar,    /*    418  kFieldName::kTradeType    */
            kFieldType::kChar,    /*    419  kFieldName::kBasisPxType    */
            kFieldType::kRepeatGroup,    /*    420  kFieldName::kNoBidComponents    */
            kFieldType::kString,    /*    421  kFieldName::kCountry    */
            kFieldType::kInt,    /*    422  kFieldName::kTotNoStrikes    */
            kFieldType::kInt,    /*    423  kFieldName::kPriceType    */
            kFieldType::kQty,    /*    424  kFieldName::kDayOrderQty    */
            kFieldType::kQty,    /*    425  kFieldName::kDayCumQty    */
            kFieldType::kPrice,    /*    426  kFieldName::kDayAvgPx    */
            kFieldType::kInt,    /*    427  kFieldName::kGTBookingInst    */
            kFieldType::kRepeatGroup,    /*    428  kFieldName::kNoStrikes    */
            kFieldType::kInt,    /*    429  kFieldName::kListStatusType    */
            kFieldType::kInt,    /*    430  kFieldName::kNetGrossInd    */
            kFieldType::kInt,    /*    431  kFieldName::kListOrderStatus    */
            kFieldType::kLocalMktDate,    /*    432  kFieldName::kExpireDate    */
            kFieldType::kChar,    /*    433  kFieldName::kListExecInstType    */
            kFieldType::kChar,    /*    434  kFieldName::kCxlRejResponseTo    */
            kFieldType::kFloat,    /*    435  kFieldName::kUnderlyingCouponRate    */
            kFieldType::kFloat,    /*    436  kFieldName::kUnderlyingContractMultiplier    */
            kFieldType::kQty,    /*    437  kFieldName::kContraTradeQty    */
            kFieldType::kUTCTimestamp,    /*    438  kFieldName::kContraTradeTime    */
            kFieldType::kString,    /*    439  kFieldName::kClearingFirm    */
            kFieldType::kString,    /*    440  kFieldName::kClearingAccount    */
            kFieldType::kInt,    /*    441  kFieldName::kLiquidityNumSecurities    */
            kFieldType::kChar,    /*    442  kFieldName::kMultiLegReportingType    */
            kFieldType::kUTCTimestamp,    /*    443  kFieldName::kStrikeTime    */
            kFieldType::kString,    /*    444  kFieldName::kListStatusText    */
            kFieldType::kLength,    /*    445  kFieldName::kEncodedListStatusTextLen    */
            kFieldType::kData    /*    446  kFieldName::kEncodedListStatusText    */
    };

};

__FIX42_END

#endif //EXCHANGESIMULATOR_FIX42_FIELDTYPEMAP_H
