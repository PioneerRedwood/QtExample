#ifndef BROWSER_HANDLER_H
#define BROWSER_HANDLER_H
#pragma once

#include <list>
#include <map>
#include <set>
#include <string>
#include <mutex>

#include <include/cef_client.h>
#include <include/cef_browser.h>
#include <include/wrapper/cef_message_router.h>
#include <include/wrapper/cef_resource_manager.h>

#include "qcview/window.h"
#include "qcview/query_handler.h"
#include "qcview/view.h"
#include "qcview/view_delegate.h"

class QCViewImpl;
class QCBase;

class QCHandler
        :
        public CefClient,
        public CefContextMenuHandler,
        public CefDisplayHandler,
        public CefLifeSpanHandler,
        public CefLoadHandler,
        public CefRequestHandler,
        public CefResourceRequestHandler {

public:
    enum class FRAME_TYPE : int {
        MAIN_FRAME = 1,
        ALL_FRAMES,
    };
public:    
    QCHandler(QCView *view)
        : view_(view) {
        // setting handler needs

    }
    ~QCHandler() {

        view_ = nullptr;
    }

  // CefClient methods:
  CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; }
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
//  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler() override { return this; }
  bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) override;

  // CefContextMenuHandler methods
  void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefContextMenuParams> params,
                           CefRefPtr<CefMenuModel> model) override;
  bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefContextMenuParams> params,
                                    int command_id,
                            EventFlags event_flags) override ;

  // CefDisplayHandler methods
  void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &url) override {

  }
  void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override {

  }
  bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                        cef_log_severity_t level,
                        const CefString &message,
                        const CefString &source,
                        int line) override {
    return false;
  }

  // CefLifeSpanHandler methods:
  bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString& target_url,
                             const CefString& target_frame_name,
                             CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                             bool user_gesture,
                             const CefPopupFeatures& popupFeatures,
                             CefWindowInfo& windowInfo,
                             CefRefPtr<CefClient>& client,
                             CefBrowserSettings& settings,
                             CefRefPtr<CefDictionaryValue>& extra_info,
                             bool* no_javascript_access) override {
    return false;
  }
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {

  }
  bool DoClose(CefRefPtr<CefBrowser> browser) override {
    return true;
  }
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {

  }

  // CefLoadHandler methods
  void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                    bool isLoading,
                                    bool canGoBack,
                            bool canGoForward) override {

  }
  void OnLoadStart(CefRefPtr<CefBrowser> browser,
                   CefRefPtr<CefFrame> frame,
                   TransitionType transition_type) override {

  }
  void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override {

  }
  void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString &errorText,
                   const CefString &failedUrl) override {

  }

  // CefRequestHandler methods
  bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefRequest> request,
                              bool user_gesture,
                      bool is_redirect) override {
    return true;
  }

  bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                const CefString &target_url,
                                CefRequestHandler::WindowOpenDisposition target_disposition,
                        bool user_gesture) override {
    return true;
  }
  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser,
                                                                         CefRefPtr<CefFrame> frame,
                                                                         CefRefPtr<CefRequest> request,
                                                                         bool is_navigation,
                                                                         bool is_download,
                                                                         const CefString &request_initiator,
                                                                 bool &disable_default_handling) override {
    return nullptr;
  }
  bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                              const CefString &origin_url,
                              int64 new_size,
                      CefRefPtr<CefCallback> callback) override {
    return true;
  }

  void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status) override {

  }

  // CefResourceRequestHandler methods
  ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           CefRefPtr<CefRequest> request,
                                   CefRefPtr<CefCallback> callback) override {
    return RV_CONTINUE;
  }
  CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                                           CefRefPtr<CefFrame> frame,
                                                   CefRefPtr<CefRequest> request) override {
    return nullptr;
  }
  void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefRequest> request,
                           bool &allow_os_execution) override {

  }


  CefRefPtr<CefBrowser> GetBrowser() const {
      return main_browser_;
  }
  void AddLocalDirectoryResourceProvider(const std::string &dir_path, const std::string &url, int priority = 0) {

  }
  void AddArchiveResourceProvider(const std::string &archive_path,
                                  const std::string &url,
                                  const std::string &password,
                                  int priority = 0) {

  }

  // Request that all existing browser windows close.
  void CloseAllBrowsers(bool force_close) {

  }
  bool TriggerEvent(const int64_t frame_id, const CefRefPtr<CefProcessMessage> msg) {

  }
  bool ResponseQuery(const int64_t query, bool success, const CefString &response, int error) {

  }
//  bool DispatchNotifyRequest(CefRefPtr<CefBrowser> browser,
//                             CefProcessId source_process,
//                             CefRefPtr<CefProcessMessage> message);
//  void NotifyTakeFocus(bool next);
//  void NotifyDragRegion(const std::vector<CefDraggableRegion> regions);

//  void SetContextMenuHandler(CefRefPtr<CefContextMenuHandler> handler) { context_menu_handler_ = handler; }
//  void SetDisplayHandler(CefRefPtr<CefDisplayHandler> handler) { display_handler_ = handler; }

  void AddRef() const {};
  bool Release() const {return true;}
  bool HasOneRef() const {return true;}
  bool HasAtLeastOneRef() const {return true;}

private:
  QCView *view_;
  int browser_count_;
  bool is_closing_;
  bool initial_navigation_;

  mutable std::mutex mtx_;
  mutable std::condition_variable close_cv_;
  CefRefPtr<CefBrowser> main_browser_;

//  CefRefPtr<CefContextMenuHandler> context_menu_handler_;
//  CefRefPtr<CefDisplayHandler> display_handler_;

  CefRefPtr<CefResourceManager> resource_manager_;
  CefRefPtr<CefMessageRouterBrowserSide> message_router_;
  CefRefPtr<QCQueryHandler> query_handler_;

//  DISALLOW_COPY_AND_ASSIGN(QCHandler);
};

#endif // BROWSER_HANDLER_H
