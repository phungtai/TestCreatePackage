//
//  ICEkycCameraProtocols.h
//  ICSdkEKYC
//
//  Created by MinhMinh on 08/12/2022.
//  Copyright © 2022 iOS Team IC - Innovation Center. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


// Xác định phiên bản khi sử dụng Máy ảnh tại bước chụp ảnh chân dung
// Mặc định là Normal
typedef enum : NSUInteger {
    Normal,     // chụp ảnh chân dung 01 hướng
    ProOval,    // chụp ảnh chân dung Oval xa gần
} VersionSdk;


// Xác định việc sử dụng máy ảnh phía trước hoặc phía sau khi chụp ảnh chân dung
// Mặc định PositionFront
typedef enum : NSUInteger {
    PositionFront,      // Máy ảnh phía trước tại bước chụp chân dung
    PositionBack,       // Máy ảnh phía sau tại bước chụp chân dung
} CameraPosition;


// Xác định kiểu giấy tờ để sử dụng
// Mặc định là IdentityCard
typedef enum : NSUInteger {
    IdentityCard,       // Chứng minh thư nhân dân, Căn cước công dân
    IDCardChipBased,    // Căn cước công dân gắn Chip
    Passport,           // Hộ chiếu
    DriverLicense,      // Bằng lái xe
    MilitaryIdCard,     // Chứng minh thư quân đội
} TypeDocument;


// Xác định việc hình thức chụp ảnh chân dung Oval
// Mặc định là FarAndNear
typedef enum : NSUInteger {
    FarAndNear,     // thực hiện chụp ảnh Oval xa và Oval gần
    OnlyFar,        // thực hiện chụp ảnh Oval xa
    OnlyNear,       // thực hiện chụp ảnh Oval gần
} VersionFaceOval;


// Xác định luồng thực hiện eKYC
// Giá trị mặc định là none
typedef enum : NSUInteger {
    none,       // không thực hiện luồng nào cả
    full,       // thực hiện eKYC đầy đủ các bước: chụp giấy tờ và chụp ảnh chân dung
    ocrFront,   // thực hiện OCR giấy tờ một bước: chụp mặt trước giấy tờ
    ocr,        // thực hiện OCR giấy tờ
    face,       // thực hiện chụp ảnh Oval xa gần và thực hiện các chức năng tuỳ vào Bật/Tắt: Compare, Verify, Mask, Liveness Face
} FlowType;


// Xác định các bước khi thực hiện eKYC
// Giá trị mặc định là stepQRCode
typedef enum : NSUInteger {
    stepQRCode,     // Quét mã QR
    stepFront,      // Chụp mặt trước giấy tờ
    stepBack,       // Chụp mặt sau giấy tờ
    stepFace,       // Chụp ảnh chân dung chủ giấy tờ
} ProgessStep;


// Xác định 'bước cuối cùng' khi Người dùng đóng SDK eKYC
typedef enum : NSUInteger {
    CancelPermission,   // Đóng SDK khi không được cấp quyền truy cập máy ảnh
    HelpDocument,       // Hướng dẫn chụp ảnh giấy tờ
    ScanQRCode,         // Quét mã QR
    CaptureFront,       // Chụp ảnh giấy tờ mặt trước
    CaptureBack,        // Chụp ảnh giấy tờ mặt trước
    HelpOval,           // Hướng dẫn chụp ảnh chân dung Oval
    AuthenFarFace,      // Chụp ảnh chân dung Oval xa
    AuthenNearFace,     // Chụp ảnh chân dung Oval gần
    HelpFaceBasic,      // Hướng dẫn chụp ảnh chân dung cơ bản
    CaptureFaceBasic,   // Chụp ảnh chân dung cơ bản
    Processing,         // Xử lý dữ liệu
    Done,               // Hoàn thành FLOW
} ScreenType;


// Xác định mức kiểm tra giấy tờ ở SDK, sử dụng Model AI Offline
// Mặc định là None
typedef enum : NSUInteger {
    None,       // Không thực hiện kiểm tra ảnh khi chụp ảnh giấy tờ
    Basic,      // Kiểm tra sau khi chụp ảnh
    MediumFlip, // Kiểm tra ảnh hợp lệ trước khi chụp (lật giấy tờ thành công → hiển thị nút chụp)
    Advance,    // Kiểm tra ảnh hợp lệ trước khi chụp (hiển thị nút chụp)
} TypeValidateDocument;


// Xác định việc sử dụng màn hình hướng dẫn "chụp ảnh khuôn mặt".
// Mặc định là HelpDefault
typedef enum : NSUInteger {
    HelpDefault,    // HelpDefault là giá trị cho bản hướng dẫn mặc định của SDK.
    HelpV1,         // HelpV1 là giá trị cho bản hướng dẫn bằng Video Full Screen
    HelpV2,         // HelpV2 là giá trị cho bản hướng dẫn nâng Video và Nội dung đi kèm
} ModelHelp;


// Xác định cơ chế kiểm tra trạng thái chụp trực tiếp của ảnh chụp chân dung
// Mặc định NoneCheckFace
typedef enum : NSUInteger {
    NoneCheckFace,  // Không thực hiện kiểm tra ảnh chân dung chụp trực tiếp hay không
    IBeta,          // Kiểm tra ảnh chân dung chụp trực tiếp hay không iBeta (phiên bản hiện tại)
    Standard,       // Kiểm tra ảnh chân dung chụp trực tiếp hay không Standard (phiên bản mới)
} ModeCheckLivenessFace;



#pragma mark - WireFrameProtocol

@protocol ICEkycCameraWireframeProtocol <NSObject>

@end

#pragma mark - ICEkycCameraPresenterProtocol

@protocol ICEkycCameraPresenterProtocol <NSObject>

@end

#pragma mark - ICEkycCameraInteractorProtocol

@protocol ICEkycCameraInteractorOutputProtocol <NSObject>

/** Interactor -> Presenter */

// trả dữ liệu kết quả tải ảnh MẶT TRƯỚC lên máy chủ
- (void) sendResultUploadSucceedFrontImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh MẶT SAU lên máy chủ
- (void) sendResultUploadSucceedBackImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG THẲNG lên máy chủ
- (void) sendResultUploadSucceedFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG XA lên máy chủ
- (void) sendResultUploadSucceedFarFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG GẦN lên máy chủ
- (void) sendResultUploadSucceedNearFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải dữ liệu QUÉT 3 CHIỀU lên máy chủ
- (void) sendResultUploadSucceedLogDataImage:(NSString *)hash;


// trả dữ liệu kết quả BÓC TÁCH THÔNG TIN MẶT TRƯỚC
- (void) sendResultGetInformationFrontCard:(NSDictionary *)result;



// trả dữ liệu kết quả BÓC TÁCH THÔNG TIN GIẤY TỜ
- (void) sendResultGetInformationCard:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA GIẤY TỜ MẶT TRƯỚC ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) sendResultCheckLivenessFrontCard:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA GIẤY TỜ MẶT SAU ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) sendResultCheckLivenessBackCard:(NSDictionary *)result;


// trả dữ liệu kết quả SO SÁNH ẢNH CHÂN DUNG (đã có) với ẢNH CHÂN DUNG vừa chụp
- (void) sendResultCompareFrontFace:(NSDictionary *)result;


// trả dữ liệu kết quả SO SÁNH ẢNH CHÂN DUNG đầy đủ (có thể lấy từ ảnh thẻ NFC) với ẢNH CHÂN DUNG vừa chụp (compare-general)
- (void) sendResultCompareFaces:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) sendResultCheckLivenessFace:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG (3 CHIỀU)
- (void) sendResultCheckLivenessFace3D:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT CÓ BỊ CHE HAY KHÔNG
- (void) sendResultCheckMaskFace:(NSDictionary *)result;


// trả dữ liệu kết quả ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) sendResultAddFace:(NSDictionary *)result;


// trả dữ liệu kết quả ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) sendResultAddCardID:(NSDictionary *)result;


// trả dữ liệu kết quả XÁC THỰC THÔNG TIN CÁ NHÂN
- (void) sendResultVerifyFace:(NSDictionary *)result;


// trả dữ liệu kết quả TÌM KIẾM THÔNG TIN CÁ NHÂN
- (void) sendResultSearchFace:(NSDictionary *)result;




@end

@protocol ICEkycCameraInteractorInputProtocol <NSObject>

- (void)setOutput:(id<ICEkycCameraInteractorOutputProtocol>)output;
- (id<ICEkycCameraInteractorOutputProtocol>)getOutputProtocol;

/** Presenter -> Interactor */


// thực hiện tải ảnh MẶT TRƯỚC (Chụp giấy tờ) lên máy chủ
- (void) handleUploadFrontImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện tải ảnh MẶT SAU (Chụp giấy tờ) lên máy chủ
- (void) handleUploadBackImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện tải ảnh CHÂN DUNG THẲNG (Chụp chân dung 1 hướng hoặc xoay mặt) lên máy chủ
- (void) handleUploadFaceImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện tải ảnh CHÂN DUNG XA (Chụp chân dung Oval) lên máy chủ
- (void) handleUploadFarFaceImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện tải ảnh CHÂN DUNG GẦN (Chụp chân dung Oval) lên máy chủ
- (void) handleUploadNearFaceImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện tải dữ liệu QUÉT 3 CHIỀU (Chụp chân dung Oval) lên máy chủ
- (void) handleUploadLogData:(NSData *)logData path:(NSURL *)path title:(NSString *)title description:(NSString *)description;


// thực hiện BÓC TÁCH THÔNG TIN GIẤY TỜ MẶT TRƯỚC (Chụp giấy tờ)
- (void) handleGetInfoFrontCard:(NSString *)front cropParam:(NSString *)cropParam type:(NSString *)type validate:(BOOL)validate;


// thực hiện BÓC TÁCH THÔNG TIN GIẤY TỜ MẶT TRƯỚC VÀ MẶT SAU (Chụp giấy tờ)
- (void) handleGetInformationCard:(NSString *)front back:(NSString *)back cropParam:(NSString *)cropParam type:(NSString *)type validate:(BOOL)validate;


// thực hiện KIỂM TRA GIẤY TỜ MẶT TRƯỚC ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) handleCheckLivenessFrontCard:(NSString *)card cropParam:(NSString *)cropParam;


// thực hiện KIỂM TRA GIẤY TỜ MẶT SAU ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) handleCheckLivenessBackCard:(NSString *)card cropParam:(NSString *)cropParam;


// thực hiện SO SÁNH ẢNH CHÂN DUNG ở GIẤY TỜ MẶT TRƯỚC với ẢNH CHÂN DUNG vừa chụp
- (void) handleCompareImageCard:(NSString *)front face:(NSString *)face;


// thực hiện SO SÁNH ẢNH CHÂN DUNG đầy đủ (có thể lấy từ ảnh thẻ NFC) với ẢNH CHÂN DUNG vừa chụp (compare-general)
- (void) handleCompareFaceOne:(NSString *)faceOne faceTwo:(NSString *)faceTwo thresLevel:(NSString *)thresLevel;


// thực hiện KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) handleCheckLivenessFace:(NSString *)face modeLiveness:(ModeCheckLivenessFace)modeLiveness;


// thực hiện KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG KIỂU 3 CHIỀU
- (void) handleCheckLiveness3DScanImageNear:(NSString *)imageNear imageFar:(NSString *)imageFar logData:(NSString *)logData modeLiveness:(ModeCheckLivenessFace)modeLiveness;


// thực hiện KIỂM TRA KHUÔN MẶT CÓ BỊ CHE HAY KHÔNG
- (void) handleCheckMaskFace:(NSString *)face;


// thực hiện ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) handleAddFaceWithInformation:(NSDictionary *)information;


// thực hiện ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) handleAddCardIDWithInformation:(NSDictionary *)information;


// thực hiện XÁC THỰC THÔNG TIN CÁ NHÂN
- (void) handleVerifyFaceWithInformation:(NSDictionary *)information;


// thực hiện TÌM KIẾM THÔNG TIN CÁ NHÂN
- (void) handleSearchFaceWithInformation:(NSDictionary *)information;


/* THỰC HIỆN CÀI ĐẶT & LƯU DỮ LIỆU */

// thực hiện CÀI ĐẶT LẠI thông tin ICEKYCSavedData
- (void) handleResetICEKYCSavedData;


// thực hiện LƯU thông tin Client Session
- (void) handleSaveClientSession:(NSString *)clientSession;


// thực hiện CÀI ĐẶT CÁC THÔNG TIN ẢNH cho ICEKYCSavedData sau khi chụp ảnh
- (void) handleSaveQRCode:(NSString *)qrCode image:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path;


// thực hiện CÀI ĐẶT CÁC THÔNG TIN ẢNH cho ICEKYCSavedData sau khi chụp ảnh
- (void) handleSaveFrontImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path cropParam:(NSString *)cropParam;


// thực hiện CÀI ĐẶT CÁC THÔNG TIN ẢNH cho ICEKYCSavedData sau khi chụp ảnh
- (void) handleSaveBackImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path cropParam:(NSString *)cropParam;


// thực hiện CÀI ĐẶT CÁC THÔNG TIN ẢNH cho ICEKYCSavedData sau khi chụp ảnh
- (void) handleSaveStraightFaceImage:(UIImage *)image cropedImage:(UIImage *)cropedImage path:(NSURL *)path;


// thực hiện CÀI ĐẶT CÁC THÔNG TIN ẢNH cho ICEKYCSavedData sau khi chụp ảnh
- (void) handleSaveFarImage:(UIImage *)farImage cropedFar:(UIImage *)cropedFar nearImage:(UIImage *)nearImage cropedNear:(UIImage *)cropedNear dataScan3D:(NSData *)dataScan3D path:(NSURL *)path;




@end

#pragma mark - ICEkycCameraViewProtocol

@protocol ICEkycCameraViewProtocol <NSObject>

/** Presenter -> ViewController */


// trả dữ liệu kết quả tải ảnh MẶT TRƯỚC lên máy chủ
- (void) showResultUploadSucceedFrontImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh MẶT SAU lên máy chủ
- (void) showResultUploadSucceedBackImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG THẲNG lên máy chủ
- (void) showResultUploadSucceedFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG XA lên máy chủ
- (void) showResultUploadSucceedFarFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải ảnh CHÂN DUNG GẦN lên máy chủ
- (void) showResultUploadSucceedNearFaceImage:(NSString *)hash;


// trả dữ liệu kết quả tải dữ liệu QUÉT 3 CHIỀU lên máy chủ
- (void) showResultUploadSucceedLogDataImage:(NSString *)hash;


// trả dữ liệu kết quả BÓC TÁCH THÔNG TIN MẶT TRƯỚC
- (void) showResultGetInformationFrontCard:(NSDictionary *)result;



// trả dữ liệu kết quả BÓC TÁCH THÔNG TIN GIẤY TỜ
- (void) showResultGetInformationCard:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA GIẤY TỜ MẶT TRƯỚC ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) showResultCheckLivenessFrontCard:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA GIẤY TỜ MẶT SAU ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) showResultCheckLivenessBackCard:(NSDictionary *)result;


// trả dữ liệu kết quả SO SÁNH ẢNH CHÂN DUNG (đã có) với ẢNH CHÂN DUNG vừa chụp
- (void) showResultCompareFrontFace:(NSDictionary *)result;


// trả dữ liệu kết quả SO SÁNH ẢNH CHÂN DUNG đầy đủ (có thể lấy từ ảnh thẻ NFC) với ẢNH CHÂN DUNG vừa chụp (compare-general)
- (void) showResultCompareFaces:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG
- (void) showResultCheckLivenessFace:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT ĐƯỢC CHỤP TRỰC TIẾP HOẶC KHÔNG (3 CHIỀU)
- (void) showResultCheckLivenessFace3D:(NSDictionary *)result;


// trả dữ liệu kết quả KIỂM TRA KHUÔN MẶT CÓ BỊ CHE HAY KHÔNG
- (void) showResultCheckMaskFace:(NSDictionary *)result;


// trả dữ liệu kết quả ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) showResultAddFace:(NSDictionary *)result;


// trả dữ liệu kết quả ĐĂNG KÝ THÔNG TIN CÁ NHÂN
- (void) showResultAddCardID:(NSDictionary *)result;


// trả dữ liệu kết quả XÁC THỰC THÔNG TIN CÁ NHÂN
- (void) showResultVerifyFace:(NSDictionary *)result;


// trả dữ liệu kết quả TÌM KIẾM THÔNG TIN CÁ NHÂN
- (void) showResultSearchFace:(NSDictionary *)result;

@end
