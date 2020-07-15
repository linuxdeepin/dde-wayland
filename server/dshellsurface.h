#ifndef DSHELLSURFACE_H
#define DSHELLSURFACE_H

#include <QtWaylandCompositor/QWaylandCompositorExtension>
#include <QtWaylandCompositor/QWaylandShellSurfaceTemplate>

QT_BEGIN_NAMESPACE
class QWaylandSurface;
class QWaylandResource;
class QWaylandSurfaceRole;
QT_END_NAMESPACE

struct wl_display;
struct wl_resource;
class DShellSurface;
class DShellSurfaceManagerPrivate;
class DShellSurfaceManager : public QWaylandCompositorExtensionTemplate<DShellSurfaceManager>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DShellSurfaceManager)
public:
    explicit DShellSurfaceManager(struct ::wl_display *display);
    explicit DShellSurfaceManager(QWaylandCompositor *compositor = nullptr);
    ~DShellSurfaceManager();

    static const struct wl_interface *interface();
    static QByteArray interfaceName();

Q_SIGNALS:
    void surfaceRequested(QWaylandSurface *surface, uint id, const QWaylandResource &resource);
    void surfaceCreated(DShellSurface *surface);

private:
    void initialize() override;

    QScopedPointer<DShellSurfaceManagerPrivate> d_ptr;
};

class DShellSurfacePrivate;
class DShellSurface : public QWaylandShellSurfaceTemplate<DShellSurface>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DShellSurface)
public:
    explicit DShellSurface(DShellSurfaceManager *manager, QWaylandSurface *surface, uint id, const QWaylandResource &resource);
    ~DShellSurface();

    QWaylandSurface *surface() const;
    uint id() const;
    void setGeometry(const QRect &rect);
    QVariant property(const QString &name) const;
    void setProperty(const QString &name, const QVariant &value);

    static const struct wl_interface *interface();
    static QByteArray interfaceName();
    static QWaylandSurfaceRole *role();
    static DShellSurface *fromResource(struct ::wl_resource *resource);

Q_SIGNALS:
    void surfaceChanged();
    void idChanged();
    void propertyChanged(const QString &name, const QVariant &value);

private:
    void initialize() override;

    QScopedPointer<DShellSurfacePrivate> d_ptr;
};

#endif // DSHELLSURFACE_H