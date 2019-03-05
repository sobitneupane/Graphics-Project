//
// Created by prasanga on 3/2/19.
//
#include <GL/glut.h>
#ifndef GRAPHICSPROJECT_ALGOS_H
#define GRAPHICSPROJECT_ALGOS_H

void putpixel(int x, int y, float r, float g, float b)
{
    glColor3f(r, g, b);
    glVertex2i(x, y);
}
void fillTriangle(float ax, float ay, float ar, float ag, float ab, float bx, float by, float br, float bg, float bb, float cx, float cy, float cr, float cg, float cb)
{
    float tempx, tempy, tempr, tempg, tempb;
    if (ay == by && by == cy)
    {
        by += 0.0001;
        cy += 0.0002;
    }
    if (ay == by)
    {
        by += 0.0001;
    }
    if (ay == cy)
    {
        cy += 0.0002;
    }
    if (by == cy)
    {
        cy += 0.0003;
    }
    if (by < ay && by < cy)
    {
        tempx = ax;
        tempy = ay;
        tempr = ar;
        tempg = ag;
        tempb = ab;
        ax = bx;
        ay = by;
        ar = br;
        ag = bg;
        ab = bb;
        if (tempy > cy)
        {
            bx = cx;
            by = cy;
            br = cr;
            bg = cg;
            bb = cb;
            cx = tempx;
            cy = tempy;
            cr = tempr;
            cg = tempg;
            cb = tempb;
        }
        else
        {
            bx = tempx;
            by = tempy;
            br = tempr;
            bg = tempg;
            bb = tempb;
        }
    }
    else if (cy < ay && cy < by)
    {
        tempx = ax;
        tempy = ay;
        tempr = ar;
        tempg = ag;
        tempb = ab;
        ax = cx;
        ay = cy;
        ar = cr;
        ag = cg;
        ab = cb;
        cx = tempx;
        cy = tempy;
        cr = tempr;
        cg = tempg;
        cb = tempb;
        if (tempy < by)
        {
            tempx = bx;
            tempy = by;
            tempr = br;
            tempg = bg;
            tempb = bb;
            bx = cx;
            by = cy;
            br = cr;
            bg = cg;
            bb = cb;
            cx = tempx;
            cy = tempy;
            cr = tempr;
            cg = tempg;
            cb = tempb;
        }
        else
        {
            cx = tempx;
            cy = tempy;
            cr = tempr;
            cg = tempg;
            cb = tempb;
        }
    }
    else
    {
        if (by > cy)
        {
            tempx = bx;
            tempy = by;
            tempr = br;
            tempg = bg;
            tempb = bb;
            bx = cx;
            by = cy;
            br = cr;
            bg = cg;
            bb = cb;
            cx = tempx;
            cy = tempy;
            cr = tempr;
            cg = tempg;
            cb = tempb;
        }
    }
    float px, py, pr, pb, pg, dx1, dx2, dx3, dr1, dr2, dr3, dg1, dg2, dg3, db1, db2, db3, sx, sy, sr, sg, sb, ex, ey, er, eg, eb, db, dg, dr;
    ;
    if (by - ay > 0)
    {
        dx1 = (bx - ax) / (by - ay);
        dr1 = (br - ar) / (by - ay);
        dg1 = (bg - ag) / (by - ay);
        db1 = (bb - ab) / (by - ay);
    }
    else
        dx1 = dr1 = dg1 = db1 = 0;

    if (cy - ay > 0)
    {
        dx2 = (cx - ax) / (cy - ay);
        dr2 = (cr - ar) / (cy - ay);
        dg2 = (cg - ag) / (cy - ay);
        db2 = (cb - ab) / (cy - ay);
    }
    else
        dx2 = dr2 = dg2 = db2 = 0;

    if (cy - by > 0)
    {
        dx3 = (cx - bx) / (cy - by);
        dr3 = (cr - br) / (cy - by);
        dg3 = (cg - bg) / (cy - by);
        db3 = (cb - bb) / (cy - by);
    }
    else
        dx3 = dr3 = dg3 = db3 = 0;

    sx = ex = ax;
    sy = ey = ay;
    sr = er = ar;
    sg = eg = ag;
    sb = eb = ab;

    if (dx1 > dx2)
    {
        for (; sy <= by; sy++, ey++)
        {
            if (ex - sx > 0)
            {
                dr = (er - sr) / (ex - sx);
                dg = (eg - sg) / (ex - sx);
                db = (eb - sb) / (ex - sx);
            }
            else
                dr = dg = db = 0;
            px = sx;
            py = sy;
            pr = sr;
            pg = sg;
            pb = sb;

            for (; px < ex; px++)
            {
                putpixel(px, py, pr, pg, pb);
                pr += dr;
                pg += dg;
                pb += db;
            }
            sx += dx2;
            sr += dr2;
            sg += dg2;
            sb += db2;
            ex += dx1;
            er += dr1;
            eg += dg1;
            eb += db1;
        }

        ex = bx;
        ey = by;
        er = br;
        eg = bg;
        eb = bb;

        for (; sy <= cy; sy++, ey++)
        {
            if (ex - sx > 0)
            {
                dr = (er - sr) / (ex - sx);
                dg = (eg - sg) / (ex - sx);
                db = (eb - sb) / (ex - sx);
            }
            else
                dr = dg = db = 0;
            px = sx;
            py = sy;
            pr = sr;
            pg = sg;
            pb = sb;
            for (; px < ex; px++)
            {
                putpixel(px, py, pr, pg, pb);
                pr += dr;
                pg += dg;
                pb += db;
            }
            sx += dx2;
            sr += dr2;
            sg += dg2;
            sb += db2;
            ex += dx3;
            er += dr3;
            eg += dg3;
            eb += db3;
        }
    }
    else
    {
        for (; sy <= by; sy++, ey++)
        {
            if (ex - sx > 0)
            {
                dr = (er - sr) / (ex - sx);
                dg = (eg - sg) / (ex - sx);
                db = (eb - sb) / (ex - sx);
            }
            else
                dr = dg = db = 0;

            px = sx;
            py = sy;
            pr = sr;
            pg = sg;
            pb = sb;
            for (; px < ex; px++)
            {
                putpixel(px, py, pr, pg, pb);
                pr += dr;
                pg += dg;
                pb += db;
            }
            sx += dx1;
            sr += dr1;
            sg += dg1;
            sb += db1;
            ex += dx2;
            er += dr2;
            eg += dg2;
            eb += db2;
        }

        sx = bx;
        sy = by;
        sr = br;
        sg = bg;
        sb = bb;
        for (; sy <= cy; sy++, ey++)
        {
            if (ex - sx > 0)
            {
                dr = (er - sr) / (ex - sx);
                dg = (eg - sg) / (ex - sx);
                db = (eb - sb) / (ex - sx);
            }
            else
                dr = dg = db = 0;

            px = sx;
            py = sy;
            pr = sr;
            pg = sg;
            pb = sb;
            for (; px < ex; px++)
            {
                putpixel(px, py, pr, pg, pb);
                pr += dr;
                pg += dg;
                pb += db;
            }
            sx += dx3;
            sr += dr3;
            sg += dg3;
            sb += db3;
            ex += dx2;
            er += dr2;
            eg += dg2;
            eb += db2;
        }
    }
}

#endif //GRAPHICSPROJECT_ALGOS_H
